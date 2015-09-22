#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



int main(int argc, char *argv[]){

	typedef struct
	{
		int magic; /* This must have the value 0x63746172. */
		int eop; /* End of file pointer. */
		int block_count; /* Number of entries in the block which are in-use. */
		int file_size[8]; /* File size in bytes for files 1..8 */
		char deleted[8]; /* Contains binary one at position i if i-th entry was deleted. */
		int file_name[8]; /* pointer to the name of the file. */
		int next; /* pointer to the next header block. */
	} hdr;
	hdr header;
	header.magic = 0x63746172;
	header.block_count=0;
	char buffer[100];
	char length[3];
	int arguments = 3;
	int fileSize = 0;
	int fileCheck = 0;
	
	//create an empty archive file
	FILE *fp;
	FILE *fp2;
	if (strcmp(argv[1], "-a") == 0){
	if (argc == 3){
		

			//-a command given, create archive if it doesnt already exist
			fp = fopen(argv[2], "rb+" );
			//make sure archive doesnt already exist
			if (fp == NULL){
				fp = fopen(argv[2], "wb");
				//set up the archive header

				fwrite(&header.magic, sizeof(int), 1, fp);
				//set eof pointer
				fseek(fp, 0, SEEK_END);
				header.eop = ftell(fp);

			}
	

			}
	
	if (argc > 3){
		fp = fopen(argv[2], "rb+");
		//make sure archive doesnt already exist
		if (fp == NULL){
			fp = fopen(argv[2], "wb");
			//set up the archive header
			fwrite(&header, sizeof(hdr), 1, fp);
			//set eof pointer
			fseek(fp, 0, SEEK_END);
			header.eop = ftell(fp);
		}
		rewind(fp);
		//check for magic number
		fread(&header, sizeof(int), 1, fp);

		//found part of the magic number, is an archive file
		if (header.magic == 0x63746172){

			//seek to the end of the file
			fseek(fp, header.eop, SEEK_SET);
			//append remaining args
			for (arguments; arguments < argc; arguments++){
				//get file size
				strncpy(length,argv[arguments],2);
				//terminate character
				length[3] = 0;
				fileSize = atoi(length);
				//set up the file size
				header.file_size[header.block_count] = fileSize;
				//increase the number of blocks
	


				//read the file
				fp2 = fopen(argv[arguments], "r");
				fread(buffer, fileSize, 1, fp2);
		
				//write the file to the archive
				fwrite(buffer,fileSize,1,fp);
				//get the new eof
				fseek(fp, 0, SEEK_END);
				header.eop = ftell(fp);
				header.next = header.eop;

				//increase block count 
				header.block_count++;
				//set filename
				header.file_name[arguments]=*argv[arguments];

			}

		}
		//back to the beginning of the archive
		rewind(fp);
		//rewrite the header into the archive
		fwrite(&header, sizeof(hdr), 1, fp);
	}
	}
	if (strcmp(argv[1], "-d") == 0){

		if (argc == 4){
			fp = fopen(argv[2], "rb+");
			fread(&header, sizeof(int), 1, fp);
			int del = rand() % 9;
			header.deleted[del] = 1;

			}
		else{
			fprintf(stderr, "invalid delete, exiting \n", 0);

		}
	}
	//error in arguments
	if (argc < 3){
		fprintf(stderr, "invalid arguemnts, exiting \n", 0);
		exit(1);
	}
	
}
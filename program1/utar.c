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
	FILE *fp,*fp2;
	int files = 0;
	char str[10];
	if (argc ==2){
		//open and read the file
		fp = fopen(argv[1], "r+");
		fread(&header, sizeof(int), 1, fp);
		//check if an archive file
		if (header.magic == 0x63746172){
			//extract the files
			header.block_count = 3;
			for (files; files < header.block_count; files++){
				sprintf(str, "%d", header.file_name[0]);
				fp2 = fopen("file", "rb+");
				//file does not exist, continue
				if (fp2 == NULL){
					fp = fopen("file", "wb");
				}
				else{
					fprintf(stderr, "File already exists, exiting \n", 0);
				}
			}
		}
	}
	else{ 
		fprintf(stderr, "invalid extract, exiting \n", 0); 
	}

}
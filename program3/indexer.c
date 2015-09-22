#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>



int main(int argc, char *argv[]){
	char * line = NULL;
	size_t len = 0;
	int currentLength = 0;
	int currentSpace = 0;
	int lines = 0;
	int ch = 0;
	struct
	{
		int position;
		int length;
	} record_descriptor;

	FILE *fp, *fp2;

	if (argc == 2){

		//open both files
		fp = fopen(argv[1], "r+");
		fp2 = fopen("indexer", "wb");

		record_descriptor.position = 0;

		//while not end of file
		while (!feof(fp)){

			ch = fgetc(fp);
			currentSpace++;
			currentLength++;

			//end of line
			if (ch == '\n'){
				record_descriptor.length = currentSpace;

				//write the struct
				fwrite(&record_descriptor, sizeof(record_descriptor), 1, fp2);
				record_descriptor.position = currentLength;
				currentSpace = 0;
			}
		}
		//text file given
	}
	else{
		//incorrect arguments
		fprintf(stderr, "incorrect number of arguments\n");
		exit(0);
	}
	fclose(fp);
	fclose(fp2);

}
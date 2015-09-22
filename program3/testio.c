#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "recordio.h"


int main(int argc, char *argv[]){
	FILE *fp;
	int ch = 0;
	if (argc == 2){
	}
	else{
		//incorrect arguments
		fprintf(stderr, "incorrect number of arguments\n");
		exit(0);
	}
	//open the file
	fp = fopen(argv[1], "r+");


	//while not end of file
	while (!feof(fp)){
		ch = fgetc(fp);
	//print out the letters
		printf("%d", ch);
		if (ch == '\n'){
	//new line
			printf("%s", "\n");
		}

	}
	fclose(fp);

}
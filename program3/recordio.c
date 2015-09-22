#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int fp = -1, fp2 = -1;
FILE *fp3;
char buffer[8];

int rio_open(const char *pathname, int flags, mode_t mode){
	//open the 2 files, 3rd if for the file pointer
	fp = open(pathname, "r+");
	fp2 = open("indexer", "wb");
	fp3 = fopen(pathname, "r+");
	//make sure no errors
	if (fp == -1 || fp2 == -1){
		//incorrect arguments
		fprintf(stderr, "file error\n");
		exit(0);
	}

}


void * rio_read(int fd, int * return_value){
	//return the read operation	
	long value = read(fp, buffer, 1);
	return (void *)value;
}

int write(int fd, const void *buf, int count){
	//write to the file
	fwrite(&buf, count, 1, fp3);

}

int lseek(int fd, int offset, int whence){
	//seek to the specified location
	lseek(fp, offset, whence);

}


int close(int fd){
	//make sure we have files
	if (fp != -1 && fp2 != -1){
		close(fp);
		close(fp2);
	}
	else{
		//incorrect arguments
		fprintf(stderr, "no descriptors passed\n");
		exit(0);
	}
}
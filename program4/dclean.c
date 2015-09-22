#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>


void List();

int main(int argc, char *argv[]){
	//generate the master copy
	List(argv, 0);
	//generate the clean copy
	List(argv, 1);
	char *args[]={"./remove",argv[1],argv[2],NULL};
	int pid=fork();
	//child
	if(pid==0){
	//execute the file removal script
	if(execvp("./remove",args)==-1){
	//error
	perror("execve failed");
	exit(1);
	}

	}else{
	//parent waits for child
	wait(2);
	
}
}


void List(char *argv[], int file){
	char *files[100];
	int lengths[100];
	char *noFiles;
	int fileNumber = file;
	int tempLength = 0;
	char *tempFile = NULL;
	char *fileLength[100];
	int position = -1; int i = 0; int j = 0; int k = 0;
	DIR *d = NULL;
	//structs for the directoy and sizes
	struct dirent *dir;
	struct stat st;

	FILE *fp, *fp1;
	//if master copy, open
	if (fileNumber == 0){
		d = opendir(argv[1]);
		fp = fopen("dclean-master.txt", "wb");


	}
	//if copy, open
	if (fileNumber == 1){
		d = opendir(argv[2]);
		fp = fopen("dclean-copy.txt", "wb");
	}
	//if directory
	if (d){

		//read until end of directory
		while ((dir = readdir(d)) != NULL){
			//remove directories
			if (dir->d_name[0] != '.'){
				//check if accessible
				if (access(dir->d_name, R_OK) == 0){
					//get the file names
					stat(dir->d_name, &st);

					if (st.st_size != 0){


						position++;
						//get the file lenghts and names
						lengths[position] = st.st_size;
						files[position] = dir->d_name;
					}
				}
				else{
					//unaccessible, store in dclean.log
					noFiles = dir->d_name;
					fp1 = fopen("dclean.log", "a");
					fprintf(fp1, "%s\n", noFiles);
				}

			}
		}
	}


	
	for (i = 0; i<position + 1; i++){

		// bubble sort
		for (j = 0; j<position; j++){
			for (k = 0; k<position - j; k++){
				if (lengths[j]>lengths[j + 1]){
					tempLength = lengths[j];
					tempFile = files[j];
					lengths[j] = lengths[j + 1];
					files[j] = files[j + 1];
					lengths[j + 1] = tempLength;
					files[j + 1] = tempFile;
				}
			}
		}


		//write the files and sizes to the copy
		fprintf(fp, "%s %d\n", files[i], lengths[i]);

	}
	//close and exit
	closedir(d);
	exit(0);
}
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	char dictionary[16];
	char buf;
	int count = 0;
	while (count<16){
		//loads the dictionary
		read(0, &buf, 1);

		dictionary[count] = buf;
		count++;


	}
	count = 0;

	//checks the size of non dictionary characters
	while (read(0, &buf, 1) == 1){

		count++;
	}

	char output[count];
	lseek(0, 0, SEEK_SET);
	count = 0;
	while (read(0, &buf, 1) == 1){

		output[count] = buf;
		count++;
		//stores characters into output
	}

	int i = 0;
	int runs = 7;
	unsigned char binChar = 0;
	char binArray[count * 9];
	int position = 0;
	int repeatCount = 0;
	int codeCount = 0;
	while (i<count - 16){
		//check first bit, continue
		runs = 7;
		while (runs >= 0){
			binChar = (output[i] >> runs) & 1;
			binArray[position] = binChar;
			position++;
			runs--;


		}
		i++;
		//printf("%c",binChar);

	}
	i = 0;
	//binArray now stores all bits
	while (i<position){
		repeatCount = 0;
		codeCount = 0;
		if (i % 9 == 0){
			//check first bit
			if (binArray[i] == 0){
				i++;
				if (binArray[i] == 1){
					repeatCount += 8;
					i++;
				}
				if (binArray[i] == 1){
					repeatCount += 4; i++;
					i++;
				}
				if (binArray[i] == 1){
					repeatCount += 2;
					i++;
				}
				if (binArray[i] == 1){
					repeatCount += 1;
					i++;
				}
				if (binArray[i] == 1){
					codeCount += 8;
					i++;
				}
				if (binArray[i] == 1){
					codeCount += 4;
					i++;
				}

				if (binArray[i] == 1){
					codeCount += 2;
					i++;
				}
				if (binArray[i] == 1){
					codeCount += 1;
					i++;
				}
				unsigned char out = dictionary[codeCount];
				//read 4 more, =repeat count
				//read 4 more =code code[dictionary]=character

				while (repeatCount >= 0){
					repeatCount--;
					write(1, &out, 1);

				}

			}
			//printf("%i",repeatCount);
			else if (binArray[i] == 1){
				//turns binChar into a character based on the 8 bits of binArray
				i++;
				binChar = binArray[i] << 7 |
					binArray[i + 1] << 6 |
					binArray[i + 2] << 5 |
					binArray[i + 3] << 4 |
					binArray[i + 4] << 3 |
					binArray[i + 5] << 2 |
					binArray[i + 6] << 1 |
					binArray[i + 7] << 0;
				i += 8;
				write(1, &binChar, 1);
				//get and write the character
			}

		}
		i++;
	}

	return 0;
}

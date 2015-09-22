#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int count = 0;
	int bitCount = 0;
	unsigned char buf;
	int pos = 0;
	char output[16];
	while (read(0, &buf, 1) == 1)
	{
		count++;

	}

	char input[count];
	lseek(0, 0, SEEK_SET);
	while (read(0, &buf, 1) == 1){

		input[pos] = buf;
		pos++;

		//reads input stream, stores into array, write out



	}
	//charcount-array storing count of symbol
	int charCount[count];
	int binArray[count * 9];
	pos = 0;
	int charCheck = 0;
	int matchFound = 0;
	while (pos<count){

		matchFound = 1;
		//set buf to the specified symbol
		buf = input[pos];

		int run = pos + 1;
		//run through the rest of count
		while (run <= count){
			if (matchFound == 1){
				charCount[pos] = 1;
			}
			//if symbol is found elsewhere add to charCount
			if (buf == input[run]){
				if (buf != ' '){
					matchFound++;
					charCount[pos] = matchFound;
					input[run] = ' ';
					//input becomes a unique symbol table
					//find highest # in char count, output location to input, get order
				}
			}
			run++;
			if (buf == ' '){
				charCount[pos] = 0;
			}
		}

		pos++;
	}
	charCount[pos] = 0;
	int x = 0;
	int xStored[count];
	int i = 0;
	int numberLoc = 0;
	int largest = 0;
	//char count functioning correctly
	int defaultCount[count];
	for (i = 0; i<count; i++){
		defaultCount[i] = charCount[i];
	}
	int test = 0;
	while (x<count){
		numberLoc = -1;
		largest = 0;
		for (i = 0; i<sizeof(charCount) / sizeof(charCount[0]); i++){
			//find largest number
			if (charCount[i]>largest){
				largest = charCount[i];
				numberLoc = i;
			}


			//numberLoc=largest number position
		}

		if (numberLoc >= 0){
			charCount[numberLoc] = -1;
			xStored[test] = input[numberLoc];
			test++;
		}

		x++;
	}
	x = 0;
	i = 0;
	while (i<test - 1){
		if (xStored[x] != ' '){
			i++;
			write(1, &xStored[x], 1);
			x++;
		}
		else{
			x++;
		}
	}

	unsigned char tes;
	//dictionary is outputting correctly, seeking to beginning?
	if (lseek(0, 0, SEEK_SET) == 0){

		int binLoc = 0;
		int freqCount = 0;
		i = 0;

		int bit = 0;
		int runs = 7;
		unsigned char bitBuf;
		while (read(0, &tes, 1) == 1){
			runs = 7;
			if (defaultCount[i] == 1){

				//check to see if its repeated, if not continue
				binArray[binLoc] = 1;
				binLoc++;
				bitCount++;
				while (runs >= 0){
					binArray[binLoc] = (tes >> runs) & 1;
					//printf("%i",binArray[binLoc]);
					runs--;
					binLoc++;
					bitCount++;
				}
				//make 9 bit arrays
			}
			if (defaultCount[i]>1){

				runs = 7;
				binArray[binLoc] = 0;
				bitCount++;
				//freqCount is dictionary
				binLoc++;

				while (runs >= 4 && runs <= 7){
					binArray[binLoc] = (freqCount >> runs - 4) & 1;
					bitCount++;

					//turn freqCount into bin? least 4 sig
					runs--;
					binLoc++;
					//place in dictionary also 4 bit into bin, reversed
				}
				freqCount++;

				while (runs >= 0 && runs <= 3){

					bitCount++;
					binArray[binLoc] = (defaultCount[i] - 1 >> runs) & 1;
					runs--;
					binLoc++;
					//4 bit repeat count so defaultCount[i] into bin, reversed
				}

			}
			i++;
			//stores each character into tes
		}
		while (binLoc % 8 != 0){
			binArray[binLoc] = 0;
			binLoc++;
			bitCount++;
		}

	}

	else{
		perror("beginning of file was not seekable");
		//error message
		return 0;
	}
	//lseek(0,0,SEEK_SET);
	int fflush();
	unsigned char outputbyte = 0;
	unsigned char temp = '1';
	int bitsWritten = 0;
	//now i have a nice binary array binArray
	//need to store into char and output

	while (bitsWritten<bitCount){
		for (i = 7; i >= 0; i--){
			temp = '1';
			if (binArray[bitsWritten] == 1){
				temp <<= (7 - i);
				outputbyte |= temp;
			}
			bitsWritten++;
		}

		write(1, &outputbyte, 1);

	}
	//bitCount=totalbits
	//at this point write binary data into necassary chars

	return 0;
}

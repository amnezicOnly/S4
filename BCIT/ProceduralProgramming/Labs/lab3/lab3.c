// A01410991
#include <stdio.h>
#include <err.h>
#include <stdlib.h>

int change_char(int c,int shift){
	// change the letter c  depending on the shift
	// deal with when shift make letter out of bound
	// 	--> before a
	//	--> after z
	int n = 0;
	if(c>=65 && c<=90){
		n = 65 + (c - 65 + shift) % 26;
	}
	if(c>=97 && c<=122){
		n = 97 + (c - 97 + shift) % 26;
	}
	return n;
}


int main(int argc, char **argv){
	if(argc!=4)
		errx(1,"Only 3 arguments are required. Usage : ./lab3 <input_file> <output_file> <shift value>\n");
	FILE *input = fopen(argv[1], "r");
	if(input==NULL)
		errx(1,"Your input file doesn't exist. Please retry with the correct path.\n");
	int shift = atoi(argv[3]);
	FILE* output = fopen(argv[2],"a");
	if(output==NULL)
		errx(1,"Your output file can't be create. Please try again.\n");
	if(shift<0){
		shift%=-26;
		shift+=26;
	}
	else
		shift%=26;

	int c;
	while ((c = fgetc(input)) != EOF){	
		if ((c>=65&&c<=90)||(c>=97&&c<=122))
				fputc(change_char(c,shift),output);
        else
            fputc(c,output);
	}


	fclose(input);
	fclose(output);
	return 0;
}

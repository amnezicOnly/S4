#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc!=3)
        errx(1,"Usage : ./anagram inputFileName.txt outputFileName.txt\n");
    FILE* input = fopen(argv[1],"r");	// comment gérer si le fichier ne s'ouvre pas ?
       
    FILE* output = fopen(argv[2],"w");	// même question
        
     int c = fgetc(input);
     if (elt == EOF)
     	fprintf(output, "Empty file.\n");
    
    // histogram
    int counter[26] = {0};

    // reading of the first sentence
    do {
        if (c>=65 && c<=90)
            counter[c-65]++;
        if (c>=97 && c<=122)
            counter[c-97]++;
    }while ((c = fgetc(input)) != '\n')
    
    c = fgetc(input);
    
    if (c == EOF)
    	errx(1,"Error : There is no second sentence.\n");

    // reading of the second sentence
    do {
        if (c>=65 && c<=90)
            counter[c-65]--;
        if (c>=97 && c<=122)
            counter[c-97]--;
    }while ((c = fgetc(input)) != EOF)

    // check if the entire array is composed of 0
    int i = 0;
    while (i<26 && counter[i]==0){
        i++;
    }

    c = (i==26);

    if (c==0)
        fprintf(output, "%d! not an anagram\n", c);
    else if (c==1)
        fprintf(output, "%d! an anagram\n", c);

    return 0;
}

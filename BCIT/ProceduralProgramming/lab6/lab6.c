// A01410991
#include <stdio.h>
#include <stdlib.h>

int mainFunction(int shift, long lower, long upper, int first, int negative1, int second, int negative2){
    // calcule first*second et regarde s'il y a dépassemeent
    // si dépassement par les négatifs, retourne -1
    // si dépassement par les positifs, retourne 1
    // retourne 0 sinon
    int result = first*second;


    return 0;
}


int main(int argc, char **argv){
	// argc : number of argument from the command line
	// argv[0] : name of the program
	// argv[>0] : user input
	if(argc!=3)
		perror("Wrong argument count, usage : ./a.out input.txt output.txt\n");
	
	// ouverture des fichiers
	FILE* input = fopen(argv[1],"r");
	if (input==NULL)
		perror("Unable to open input file.\n");
	FILE* output = fopen(argv[2],"w");
	if (output==NULL)
		perror("Unable to open output file.\n");
	
	// récupération et traitement du shift
	int shift = 0;
	char temp;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!='-')
			shift = shift*10 + (temp-'0');

    // si fichier vide
    if(temp=='E' || temp==EOF){
        fputs("Input file should contains exactly 1 or 3 values.\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

	if(temp=='-'){	// le shift ne peut pas être négatif
        fputs("The first value has to be strictly greater than 0.\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

    // si le shift n'est pas compris entre 4 et 64
    if(shift<4 || shift>64){
        fputs("The first has to be strictly greater than 3 and strictly lower than 65.\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

    // on calcule les bornes inférieures et supérieures
    long upper = 1;
	for(int i=1; i<shift-1; i++){
		upper<<=1;
        upper++;
	}

    long lower = ~upper;

	
	int first = 0;
	int negative1 = 0;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
        if(temp=='-')
			negative1 = 0;
		else
			first = first*10 + (temp-'0');
	}
		
	if(temp=='E'){	// si le fichier ne contient qu'un seul nombre
        fprintf(output,"min: %ld\t0x%.16lx\n",lower,lower);
        fprintf(output,"max: %ld\t0x%.16lx\n",upper,upper);
		fclose(input);
		fclose(output);
		return 0;
	}

	if (temp=='E' || temp==EOF){	// si l'input n'est pas bon
		// mauvais input
        fputs("Input file should contains 1 or 3 values exactly.\n",output);
        fclose(output);
        fclose(input);
        return 0;
    }

    if(negative1==1)
        first = -first;


	int second = 0;
    int negative2 = 0;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
        if(temp=='-')
            negative2 = 1;
        else
		    first = first*10 + (temp-'0');
    }

    if(negative2==1)
        second = -second;

    int enfin = mainFunction(shift,upper,lower,first,negative1,second,negative2);

    if(enfin==-1)
        fprintf(output,"%ld\n",lower);
    if(enfin==0)
        fprintf(output,"%d\n",(first*second));
    if(enfin==1)
        fprintf(output,"%ld\n",upper);
	
	fclose(input);
	fclose(output);
	return 0;
}

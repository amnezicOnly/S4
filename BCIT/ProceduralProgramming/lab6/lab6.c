// A01410991
#include <stdio.h>
#include <stdlib.h>

int mainFunction(int shift, long first, int negative1, long second, int negative2){
    // calcule first*second et regarde s'il y a dépassemeent
    // si dépassement par les négatifs, retourne -1
    // si dépassement par les positifs, retourne 1
    // retourne 0 sinon
    long result = first*second;
    long mask = 1;
    mask<<=(shift-1);   // mask sera un nombre négatif de la forme 10...0
    if(negative1==negative2){   // le produit de 2 termes de même signe est positif
        if((result & mask)==mask && result!=0)   //si bit de signe de result ET 1 == 1
            // si le bit de signe de result est différent de 0 (donc égal à 1)
            // ça va renvoyer 1 car il y aura un dépassement par les positifs
            return 1;
        // si la condition retourne 0, c'est qu'il n'y a pas eu de dépassement
        // donc on retourne 0
        return 0; 
    }
    else{   // si negative1!=negative2 --> result est négatif
        if((result & mask)!=mask && result!=0)   // si bit de signe de mask ET 1 == 0
            // si la condition est remplie ça veut dire que le résultat et positif
            // donc dépassement par kes négatifs donc on renvoie -1
            return -1;
        // sinon c'est que le résultat ne pose pas de problème
        return 0;
    }
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
	
	// récupération du shift
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
    long upper = 1<<(shift-1);
    upper--;
    long lower = ~upper;

	// si le fichier contient plus d'une ligne, on récupère le premier facteur
	long first = 0;
	int negative1 = 1;
    int state = 0;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
        state = 1;
        if(temp=='-')
			negative1 = 0;
		else
			first = first*10 + (temp-'0');
	}
		
	if((temp=='E' || temp==EOF) && state==0){	// si le fichier ne contient qu'un seul nombre
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

    // s'il y avait un moins, on passe le nombre en négatif
    if(negative1==0)
        first = -first;

    // récupération du second facteur
	long second = 0;
    int negative2 = 1;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
        if(temp=='-')
            negative2 = 0;
        else
		    second = second*10 + (temp-'0');
    }

    //printf("Here\n");
    // s'il y avait un moins, on passe le nombre en négatif
    if(negative2==0)
        second = -second;

    // on regarde s'il y a un dépassement
    int enfin = mainFunction(shift,first,negative1,second,negative2);

    if(enfin==-1)   // si dépassement par les négatifs
        fprintf(output,"%ld\n",lower);
    if(enfin==0)    // si aucun dépassement, cas normal
        fprintf(output,"%ld\n",(first*second));
    if(enfin==1)    // si dépassement par les positifs
        fprintf(output,"%ld\n",upper);
	
    // on referme les fichiers
	fclose(input);
	fclose(output);
    // on sort du programme
	return 0;
}

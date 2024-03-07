// A01410991
//#include <stdio.h>
//#include <stdlib.h>


void writeOutputOne(FILE* output, int shift){
	// écrit les valeurs du minimum et du maximum en fonction de shift dans le fichier output
	// close input et output
	
}



int main(int argc, char **argv){
	// argc : number of argument from the command line
	// argv[0] : name of the program
	// argv[>0] : user input
	if(argc!=3){
		perror("Wrong argument count, usage : ./a.out input.txt output.txt\n");
	
	// ouverture des fichiers
	FILE* input = fopen(argv[1],"r");
	if (input==NULL)
		perror("Unable to open input file.\n");
	FILE* output = fopen(argv[2],"w");
	if (output==NULL)
		perror("Unable to open output file.\n");
	
	// récupération des valeurs
	int shift = 0;
	char temp;
	int negative = 1;
	while((temp=fgetc(input))!='E' && temp!='\n'){
		if(temp=='-')
			negative = 0;
		else
			shift = shift*10 + (temp-'0');
	}
	if(negative==0)	// le shift ne peut pas être négatif
		// cas d'erreur
	
	if(temp=='E')	// si le fichier ne contient qu'un seul nombre
		writeOutputOne(output,shift);
		
	int first = 0;
	nagative = 0;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
		if(temp=='-')
			negative = 0;
		else
			first = first*10 + (temp-'0');
	}
		
	
	if (temp=='E' || temp==EOF)	// si l'input n'est pas bon
		// mauvais input
	
	int second = 0;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF)
		first = first*10 + (temp-'0');
	
	
	
	
	return 0;
}

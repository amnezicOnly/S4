// A01410991
// A01410993
// A01410988
// A01410994

#include<stdio.h>
#include<stdlib.h>
#include<err.h>

struct Particule{
	short X;	// position en X
	short Y;	// position en Y
	short velX;	// à chaque période : X+=velX
	short velY;	// à chaque période : Y+=velY
};

short getValue(FILE* input){	// renvoie la première valeur en int depuis le début du fichier à partir du pointeur
	int res = 0;
	char temp;
	while((temp=fgetc(input))!=EOF && temp!=',' && temp!='\n'){
		res = (res*10)+(temp-'0');
	}
	if(temp==EOF)
		return -1;
	return (short)res;
}

struct Particule createParticule(short x, short y, short velx, short vely){
	struct Particule res;
	res.X = x;
	res.Y = y;
	res.velX = velx;
	res.velY = vely;
}

short searchParticule(struct Particule* liste, size_t size, short x, short y){
	for(size_t i=0; i<size; i++){	// si la particule existe déjà, on ne l'ajoute pas
		if(liste[i].X==x && liste[i].Y==y)
			return (short)i;
	}
	return -1;
}

void addParticule(struct Particule* liste, size_t* size, struct Particule nouveau){
	// la liste n'est pas vide
	if(searchParticule(liste,*size,nouveau.X,nouveau.Y)!=-1){
		// on ne rajoute une particule que si elle n'est pas présente dans la liste
		(*size)++;
		liste = realloc(liste,(*size)*sizeof(struct Particule));
		liste[(*size)-1] = nouveau;
	}
}

void play(struct Particule* liste, size_t size, short width, short height){
	// va déplacer chaque particule de velX et velY
	// tri (en place) à chaque nouvelle actualisation des coordonnées (idée : mettre les particules qui se collisionnent à la fin de la liste pour pouvoir réduire la taille de la liste
	
	// boucle de mouvement des particules
	for(size_t i=0; i<size; i++){
		liste[i].X+=liste[i].velX;
		if(liste[i].X<=0 || liste[i].X==width-1)	// si ça tape une colonne
			liste[i].velX*=-1;
		liste[i].Y+=liste[i].velY;
		if(liste[i].Y<=0 || liste[i].X==height-1)	// si ça tape une ligne
			liste[i].velY*=-1;
	}
}

void writeOutput(FILE* output, struct Particule* liste, size_t* size, short width, short height){
	// va d'abord afficher la ligne du haut
	short count = 0;
	for(short i=-1; i<=width; i++){
		fputc('*',output);
	}
	fputc('\n',output);
	// pour chaque ligne
	for(short i=0; i<height; i++){
		fputc('*',output);	// première colonne
		for(short j=0;i<width;j++){
			if(searchParticule(liste,*(size),liste[count].X,liste[count].Y)!=-1){
				fputc('+',output);
				count++;
			}
			else{
				fputc(' ',output);
			}
		}	
		fputc('*',output);	// deuxième colonne
		fputc('\n',output);	// retour à ligne
	}
	
	// et enfin on va afficher la dernière ligne
	for(short i=-1; i<=width; i++){
		fputc('*',output);
	}
}

int main(int argc, char** argv){
	if(argc!=3){
		errx(1,"Usage : ./program input.txt output.txt\n");
	}
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		errx(1,"Unable to open input file.\n");	
	
	struct Particule truc;
	
	short width = getValue(input);	// récupère la largeur de la fenêtre à partir de l'input
	short height = getValue(input);	// récupère la hauteur de la fenêtre à partir de l'input
	short lapNumber = getValue(input);	// récupère le nombre de tours
	
	short x = getValue(input);
	short y = getValue(input);
	short velx = getValue(input);
	short vely = getValue(input);
	
	// création de la liste et ajout de la première particule
	struct Particule* liste = malloc(sizeof(struct Particule));
	size_t* size = malloc(sizeof(size_t));
	(*size) = 1;
	liste[0] = createParticule(x,y,velx,vely);
	
	short temp = getValue(input);
	while(temp!=-1){
		// ajout successif des particules dans liste à partir de l'input
		x = temp;
		y = getValue(input);
		velx = getValue(input);
		vely = getValue(input);
		addParticule(liste,size,createParticule(x,y,velx,vely));
		temp = getValue(input);
	}
	
	fclose(input);
	
	// simule les tours dans liste
	for(short i=0; i<lapNumber; i++)
		play(liste, (*size), width, height);
	
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		errx(1,"Unable to open output file.\n");	
	// écrit la fenêtre et les particules dans le fichier output
	writeOutput(output,liste,size,width,height);
	fclose(output);
		
	return 0;
}

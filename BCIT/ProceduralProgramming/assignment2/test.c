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
	short velX;	// a chaque periode : X+=velX
	short velY;	// a chaque periode : Y+=velY
};

short getValue(FILE* input){	// renvoie la premiere valeur en int depuis le debut du fichier a partir du pointeur
	int res = 0;
    	int negative = 1;   // si le nombre est negatif
    	int state = 1;  // indique si on a deja lu un nombre
	char temp;
	while((temp=fgetc(input))!=EOF && temp!=',' && temp!='\n' && temp!='.'){
        	if(temp=='-' && negative==1){
            		negative=0;    // indique que le resultat retourne sera negatif
		}
        	else if(temp=='-' && negative==0)
            		return -500;    // si on deja lu le signe -

        	else if(temp>='0' && temp<='9'){
        		state = 0;
		    	res = (res*10)+(temp-'0');
		}
	}

	if(temp==EOF || (temp==',' && state==1) || (temp=='\n' && state==1) || temp=='.')
        // si le fichier est vide ou que les coordonnees ne sont pas mises coorectement
		return -500;
	if(negative==0)
        	return (short)((-1)*res);
    	return (short)res;
}

void printListe(struct Particule* liste, size_t size){
	printf("Liste : ");
	for(size_t i=0; i<size; i++)
		printf("(X: %hd, Y: %hd, velX: %hd, velY: %hd)-->",liste[i].X,liste[i].Y,liste[i].velX,liste[i].velY); 
	printf("NULL (%zu)\n",size);
}

short searchParticule(struct Particule* liste, size_t size, short x, short y){
	for(size_t i=0; i<size; i++){	// si la particule existe deja, on ne l'ajoute pas
		if(liste[i].X==x && liste[i].Y==y)
			return (short)i;
	}
	return -1;
}

void addParticule(struct Particule* liste, size_t* size, short x, short y, short velx, short vely){
	// la liste n'est pas vide
	if(searchParticule(liste,*size,x,y)==-1){
		// on ne rajoute une particule que si elle n'est pas presente dans la liste
		(*size)++;
		liste = realloc(liste,(*size)*sizeof(struct Particule));
		liste[(*size)-1].X=x;
		liste[(*size)-1].Y=y;
		liste[(*size)-1].velX=velx;
		liste[(*size)-1].velY=vely;
		
	}
}

void play(struct Particule* liste, size_t size, short width, short height){
	// va deplacer chaque particule de velX et velY
    	for(size_t i = 0; i<size; i++){
    		int state = 0;
        	if(liste[i].X+liste[i].velX<=0 || liste[i].X+liste[i].velX>=width-1){   // cas où une colonne est touchee
            		if(liste[i].X+liste[i].velX==0 || liste[i].X+liste[i].velX==width-1){
                		liste[i].X += liste[i].velX;
            		}
            		else if (liste[i].X+liste[i].velX<0){
                		liste[i].X = (-liste[i].velX)-liste[i].X;
            		}

            		else if(liste[i].X+liste[i].velX>width-1){
                		liste[i].X = (width-1)-((liste[i].X+liste[i].velX)%(width-1));
            		}
            		liste[i].velX*=(-1);
            		state+=1;
        
        	}
        
        	if(liste[i].Y+liste[i].velY<=0 || liste[i].Y+liste[i].velY>=height-1){   // cas où une ligne est touchee
            		if(liste[i].Y+liste[i].velY==0 || liste[i].Y+liste[i].velY==height-1){
                		liste[i].Y += liste[i].velY;
            		}
            		else if (liste[i].Y+liste[i].velY<0){
                		liste[i].Y = (-liste[i].velY)-liste[i].Y;
            		}

            		else if(liste[i].Y+liste[i].velY>height-1){
                		liste[i].Y = (height-1)-((liste[i].Y+liste[i].velY)%(height-1));
            		}
            		liste[i].velY*=(-1);
            		state+=2;
        	}
        
        	if(state==1){
        		liste[i].Y+=liste[i].velY;
        	}
        	if(state==2){
        		liste[i].X+=liste[i].velX;
        	}
        	if(state==0){
        		liste[i].X+=liste[i].velX;
        		liste[i].Y+=liste[i].velY;
        	}
    	}
}

void checkCollision(struct Particule* liste,size_t size){
	// on verifie que plusieurs particules ne sont pas sur la meme coordonnee
	// si oui, on modifie les coordonnees de toutes ces occurences a 25 et -2
	size_t i = 0;
    	while(i<size){
		// si on croise deux particules qui ont les memes coordonnees
		int state = 1;
		if(liste[i].X!=25 && liste[i].Y!=-2){
			for(int j=i+1; j<size; j++){
				if(liste[j].X==liste[i].X && liste[j].Y==liste[i].Y){
					liste[j].X = 25;
					liste[j].Y = -2;
					state = 0;
				}
			}
		}
		if(state==0){
			liste[i].X = 25;
			liste[i].Y = -2;
		}
		i++;
	}
}

void writeOutput(FILE* output, struct Particule* liste, size_t size, short width, short height){
	for(int i=-1; i<=width; i++)
		fputc('*',output);
	fputc('\n',output);
	for(short i = height-1; i>=0; i--){
		// pour chaque ligne (de height-1 a 0)
		fputc('*',output);	// colonne
		for(short j = 0; j<width; j++){
			// pour chaque colonne (de 0 a width-1)
			int temp = searchParticule(liste,size,j,i);
			// Si (j,i) existe 
			if(temp!=-1)
				fputc('+',output);
			else
				fputc(' ',output);
		}
		fputc('*',output);	// colonne
		fputc('\n',output);
	}
	for(int i=-1; i<=width; i++)
		fputc('*',output);
}

int main(int argc, char** argv){
	if(argc!=3){
		perror("Usage : ./program input.txt output.txt\n");
        return 0;
	}
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL){
		perror("Unable to open input file.\n");
        	return 0;
    	}

    	FILE* output = fopen(argv[2],"w");
	if(output==NULL){
		perror("Unable to open output file.\n");	
        	return 0;
    	}
    
	short width = getValue(input);	// recupere la largeur de la fenetre a partir de l'input
	short height = getValue(input);	// recupere la hauteur de la fenetre a partir de l'input
	short lapNumber = getValue(input);	// recupere le nombre de tours

    if(width<1 || height<1 || width>20 || height>20){
        fputs("Error\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

    // Recuperation des infos de la premiere particule    
	short x = getValue(input);
	short y = getValue(input);
	short velx = getValue(input);
	short vely = getValue(input);	

    if(x<0 || x>=width || y<0 || y>=height || x==-500 || y==-500 || velx==-500 || vely==-500){
        fputs("Error\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

	// creation de la liste et ajout de la premiere particule
	struct Particule* liste = malloc(sizeof(struct Particule));
	size_t* size = malloc(sizeof(size_t));
	(*size) = 1;
	liste[0].X=x;
	liste[0].Y=y;
	liste[0].velX=velx;
	liste[0].velY=vely;
	
	short temp = getValue(input);
    	// ajout successif des particules dans liste a partir de l'input
	while(temp!=(short)'E' && temp!=-500){
		x = temp;
		y = getValue(input);
		velx = getValue(input);
		vely = getValue(input);
        	//printListe(liste,(*size));
        	// s'il y a un probleme dans les coordonnees
        	if(x<0 || x>=width || y<0 || y>=height || velx==-500 || vely==-500){
           		fputs("Error\n",output);
				free(liste);
            	fclose(input);
            	fclose(output);
            	return 0;
			}
		printListe(liste,*size);
		addParticule(liste,size,x,y,velx,vely);
		temp = getValue(input);
	}
	printListe(liste,*size);
	if (temp == -500) {
		fputs("Error\n",output);
		free(liste);
		fclose(input);
		fclose(output);
		return 0;
	}

	fclose(input);

	//printListe(liste,*size);
	for(short i = 0; i<lapNumber; i++){
		play(liste,*size,width,height);
		checkCollision(liste,*size);		
	}


	
	// ecrit la fenetre et les particules dans le fichier output
	writeOutput(output,liste,*size,width,height);	
   	free(liste);
	fclose(output);
		
	return 0;
}

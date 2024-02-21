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
    	int negative = 1;   // si le nombre est négatif
    	int state = 1;  // indique si on a déjà lu un nombre
	char temp;
	while((temp=fgetc(input))!=EOF && temp!=',' && temp!='\n'){
        	if(temp=='-' && negative==1)
            		negative==0;    // indique que le résultat retourné sera négatif
        	if(temp=='-' && negative==0)
            		return -500;    // si on déjà lu le signe -
        	else if(temp>='0' && temp<='9'){
        		state = 0;
		    	res = (res*10)+(temp-'0');
		}
	}
	
	if(temp==EOF || (temp==',' && state==1) || (temp=='\n' && state==1))
        // si le fichier est vide ou que les coordonnées ne sont pas mises coorectement
		return -500;
	if(negative==0)
        	res*=(-1);
    	return (short)res;
}

void printListe(struct Particule* liste, size_t size){
	printf("Liste : ");
	for(size_t i=0; i<size; i++)
		printf("(X: %hd, Y: %hd, velX: %hd, velY: %hd)-->",liste[i].X,liste[i].Y,liste[i].velX,liste[i].velY); 
	printf("NULL (%zu)\n",size);
}

short searchParticule(struct Particule* liste, size_t size, short x, short y){
	for(size_t i=0; i<size; i++){	// si la particule existe déjà, on ne l'ajoute pas
		if(liste[i].X==x && liste[i].Y==y)
			return (short)i;
	}
	return -1;
}

void addParticule(struct Particule* liste, size_t* size, short x, short y, short velx, short vely){
	// la liste n'est pas vide
	if(searchParticule(liste,*size,x,y)==-1){
		// on ne rajoute une particule que si elle n'est pas présente dans la liste
		(*size)++;
		liste = realloc(liste,(*size)*sizeof(struct Particule));
		liste[(*size)-1].X=x;
		liste[(*size)-1].Y=y;
		liste[(*size)-1].velX=velx;
		liste[(*size)-1].velY=vely;
		
	}
}

void play(struct Particule* liste, size_t size, short width, short height){
	// va déplacer chaque particule de velX et velY
    for(size_t i = 0; i<size; i++){
    	int state = 0;
    	printf("Avant mouvement (%zu): (X: %hd, Y: %hd)\n",i,liste[i].X,liste[i].Y);
        if(liste[i].X+liste[i].velX<=0 || liste[i].X+liste[i].velX>=width-1){   // cas où une colonne est touchée
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
        if(liste[i].Y+liste[i].velY<=0 || liste[i].Y+liste[i].velY>=height-1){   // cas où une colonne est touchée
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
            state+=0;
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
    	printf("Après mouvement (%zu): (X: %hd, Y: %hd)\n",i,liste[i].X,liste[i].Y);
    }
}

void deleteParticule(struct Particule** liste, size_t* size, short x, short y, size_t n){
    // supprime toutes les occurences des particules où X==x et Y==y à partir de l'index n dans liste
    for(size_t i=n; i<(*size); i++){
        if((*liste)[i].X==x && (*liste)[i].Y==y){
            for(size_t j=i; j<(*size)-1; j++)
                liste[i] = liste[i+1];
            (*size)--;
            // on réduit la taille de la liste à chaque fois qu'on trouve deux éléments qui ont les mêmes coordonnées
            liste = malloc((*size)*sizeof(struct Particule));
        }
    }
}


void checkCollision(struct Particule** liste,size_t* size){
    // vérifie qu'il n'y a aucune Particule qui a les mêmes coordonnées qu'une autre Particule
    for(size_t i = 0; i<(*size); i++)
       deleteParticule(liste,size,(*liste)[i].X, (*liste)[i].Y, i); 
}


struct Particule* sortList(struct Particule* liste, size_t size){
        struct Particule* res =malloc(size*sizeof(struct Particule));
        res[0] = liste[0];
        size_t size_res = 1;
        while(size_res!=size){  // tant que toute la liste n'y est pas passée
            size_t i = 0;
            while(i<size_res && (liste[size_res].Y<res[i].Y || (liste[size_res].Y==res[i].Y && liste[size_res].X<res[i].X)))
                i++;
            for(size_t j=size_res-1; j>i; j--)
                res[j] = res[j-1];
            res[i] = liste[size_res];
            size_res++;
        }
}


/*struct Particule* sortList(struct Particule* liste,size_t size){
    struct Particule* res = malloc(sizeof(struct Particule));
    res[0] = liste[0];
    size_t res_size = 1;
    while(res_size!=size){
        size_t i = 0;
        struct Particule temp = liste[0];
        while(i<res_size){
    		printf("Boucle infinie ?\n");
           	while(temp.Y>liste[i].Y || (temp.Y==liste[i].Y && temp.X<liste[i].X))
                	i++;
        	}
        	res_size++;
        	res = realloc(res,(res_size)*sizeof(struct Particule));
        	for(size_t j = res_size-1; j>i; j--)
            		res[j] = res[j-1];
        	res[i] = temp;
   	}
    return res;
}*/

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
    
	short width = getValue(input);	// récupère la largeur de la fenêtre à partir de l'input
	short height = getValue(input);	// récupère la hauteur de la fenêtre à partir de l'input
	short lapNumber = getValue(input);	// récupère le nombre de tours

    if(width<1 || height<1){
    	printf("width: %hd, height: %hd, lapNumber: %hd\n",width,height,lapNumber);
        fputs("Error 1\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

    // Récupération des infos de la première particule    
	short x = getValue(input);
	short y = getValue(input);
	short velx = getValue(input);
	short vely = getValue(input);	

    if(x<0 || x>=width || y<0 || y>=height || x==-500 || y==-500 || velx==-500 || vely==-500){
        fputs("Error 2\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

	// création de la liste et ajout de la première particule
	struct Particule* liste = malloc(sizeof(struct Particule));
	size_t* size = malloc(sizeof(size_t));
	(*size) = 1;
	liste[0].X=x;
	liste[0].Y=y;
	liste[0].velX=velx;
	liste[0].velY=vely;
	
	short temp = getValue(input);
    	// ajout successif des particules dans liste à partir de l'input
	while(temp!=-500){
		x = temp;
		y = getValue(input);
		velx = getValue(input);
		vely = getValue(input);
        	//printListe(liste,(*size));
        	// s'il y a un problème dans les coordonnées
        	if(x<0 || x>=width || y<0 || y>=height || velx==-500 || vely==-500){
           		fputs("Error 3\n",output);
            		fclose(input);
            		fclose(output);
            		return 0;
        	}
		//printf("Ajout de : X=%hd, Y=%hd, velX=%hd, velY=%hd\n",x,y,velx,vely);
		addParticule(liste,size,x,y,velx,vely);
		temp = getValue(input);
	}
	fclose(input);
	
    	//printListe(liste,(*size));
	// simule les tours dans liste
	/*for(short i=0; i<lapNumber; i++){
        	// simulation du mouvement des particules
		play(liste, (*size), width, height);
        	// enlève toutes particules qui ont les mêmes coordonnées
       		checkCollision(&liste, size);
    	}*/
    	//printListe(liste,(*size));
	//printf("here it's ok\n");
	
    	// Crée une nouvelle liste de Particule qui est la liste triée
    	struct Particule* end = sortList(liste,(*size));
    	printf("Here it's ok\n");
        return 0;
        printListe(end,*size);
    	free(liste);

	// écrit la fenêtre et les particules dans le fichier output
	writeOutput(output,end,size,width,height);
   	free(end);
	fclose(output);
		
	return 0;
}

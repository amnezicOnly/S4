// A01410991
#include <stdio.h>
#include <stdlib.h>

struct Coord{
	short X;
	short Y;
};


int getValue(FILE* input){
	int state = 1;
	int res = 0;
	int temp;
	while((temp=fgetc(input))!='E' && temp!=',' && temp!='\n'){
		state = 0;
		res = res*10 + (temp-'0');
	}
	if(state==1 && temp=='E')
		return -2;
	else if(state==1 && temp!='E')
		return -1;
	else
		return res;
}



void addCoord(struct Coord** coords, size_t* size, short x, short y) {
    short index = 0;
    for (size_t temp = 0; temp < *size; temp++) {
        if ((*coords)[temp].X == x && (*coords)[temp].Y == y)
            return;
    }
    while (index < *size) {
        if ((*coords)[index].Y < y || ((*coords)[index].Y == y && (*coords)[index].X > x)) {
            break;
        }
        index++;
    }

    // Incrémenter la taille de la liste
    (*size)++;

    // Réallocation de la mémoire pour agrandir la liste de 1
    *coords = realloc(*coords, (*size) * sizeof(struct Coord));
    if (*coords == NULL) {
        // Gérer l'échec de la réallocation
        fprintf(stderr, "Erreur lors de la réallocation de la mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // Déplacement des éléments pour insérer le nouvel élément à la position correcte
    for (size_t i = *size - 1; i > index; i--) {
        (*coords)[i] = (*coords)[i - 1];
    }

    // Insérer le nouvel élément à l'index approprié
    (*coords)[index].X = x;
    (*coords)[index].Y = y;
}



void fillColumn(struct Coord** coords, size_t* size, short x, short oldY, short tempY){
	short up = 1;
	if(oldY>tempY)
		up = -1;
	oldY+=up;
	while(oldY!=tempY){
		addCoord(coords,size,x,oldY);
		oldY+=up;
	}
}

void fillDiag(struct Coord** coords, size_t* size, short oldX, short oldY, short tempX, short tempY){
	short up = 1;
	short right = 1;
	if(oldX>tempX)
		right = -1;
	if(oldY>tempY)
		up = -1;
	oldX+=right;
	oldY+=up;
	while(oldX!=tempX && oldY!=tempY){
		addCoord(coords,size,oldX,oldY);
		oldX+=right;
		oldY+=up;
	}	
}

void writeFile(FILE* output, struct Coord* coords, size_t* size){
	size_t i = 0;
	while(i<(*size)-1 && coords[i].Y!=0){
		short j;
		if(i+1<*size-1 && coords[i].Y!=coords[i+1].Y){
			for(j=0; j<coords[i].X; j++){
				fputc(' ',output);
			}
			fputc('*',output);
		}
		else if(i+1<*size-1 && coords[i].Y==coords[i+1].Y){
			for(j=0; j<coords[i].X; j++){
				fputc(' ',output);
			}
			for(j=coords[i].X; j<=coords[i+1].X; j++){
				fputc('*',output);
			}
			i++;
			 
		}
		i++;
		fputc('\n',output);
	}
	
	while(i<*size){
		short j = 0;
		if(i+1<*size && coords[i].Y!=coords[i+1].Y){
			for(j=0; j<coords[i].X; j++){
				fputc(' ',output);
			}
			fputc('*',output);
		}
		else if(i+1<*size && coords[i].Y==coords[i+1].Y){
			for(j=0; j<coords[i].X; j++){
				fputc(' ',output);
			}
			for(j=coords[i].X; j<=coords[i+1].X; j++){
				fputc('*',output);
			}
			i++;
		}
		i++;
	}
}


int main(int argc, char** argv){
	if(argc!=3){
		perror("Usage : ./lab4 input.txt output.txt\n");
	}
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		perror("Unable to open input.txt\n");
	
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		perror("Unable to open output.txt\n");
	
	int oldX = getValue(input);
	if(oldX==-1 || oldX==-2){
		fputs("Error\n",output);
		fclose(input);
		fclose(output);
		return 0;
	}
	int oldY = getValue(input);
	if(oldY==-1 || oldY==-2){
		fputs("Error\n",output);
		fclose(input);
		fclose(output);
		return 0;
	}
	
	struct Coord* coords = malloc(sizeof(struct Coord));
	size_t* size = malloc(sizeof(size_t));
	*size = 1;
	
	coords[0].X = oldX;
	coords[0].Y = oldY;	
	
	
	int beginX = oldX;
	int beginY = oldY;
	int tempX;
	int tempY;
	int temp;
	
	while((temp = getValue(input))!=-2 && temp!=-1 && temp>=0 && temp<=10){
		tempX = (short)temp;
		tempY = (short)getValue(input);
		if(tempY==-1 || tempY==-2){
			fputs("Error\n",output);
			fclose(input);
			fclose(output);
			return 0;
		}
		
		if(oldX==tempX){
			fillColumn(&coords,size,(short)oldX,(short)oldY,tempY);
		}
		else if(oldX!=tempX && oldY!=tempY){
			fillDiag(&coords,size,(short)oldX,(short)oldY,tempX,tempY);
		}
		addCoord(&coords,size,tempX,tempY);
		
		oldX = (int)tempX;
		oldY = (int)tempY;
	}
	if(tempX!=beginX || tempY!=beginY){
		fputs("Error\n",output);
		fclose(input);
		fclose(output);
		return 0;
	}
	fclose(input);
	writeFile(output,coords,size);
	fclose(output);
	
	return 0;
}

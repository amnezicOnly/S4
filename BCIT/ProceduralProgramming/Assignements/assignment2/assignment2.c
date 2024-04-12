// A01410991
// A01410993
// A01410988
// A01410994

#include<stdio.h>
#include<stdlib.h>

struct Particule{
	short X;	// X position
	short Y;	// Y position
	short velX;	// X direction
	short velY;	// Y direction
};

short getValue(FILE* input){
	int res = 0;
   	int negative = 1;
    	int state = 1;
	char temp;
	while((temp=fgetc(input))!=EOF && temp!=',' && temp!='\n' && temp!='.'){
        	if(temp=='-' && negative==1){
            		negative=0;
		}
        	else if(temp=='-' && negative==0)
            		return -500;

        	else if(temp>='0' && temp<='9'){
        		state = 0;
		    	res = (res*10)+(temp-'0');
		}
	}

	if(temp==EOF || (temp==',' && state==1) || (temp=='\n' && state==1) || temp=='.')
		return -500;
	if(negative==0)
        	return (short)((-1)*res);
    	return (short)res;
}


short searchParticule(struct Particule* liste, size_t size, short x, short y){
	for(size_t i=0; i<size; i++){	// si la particule existe déjà, on ne l'ajoute pas
		if(liste[i].X==x && liste[i].Y==y)
			return (short)i;
	}
	return -1;
}

void addParticule(struct Particule* liste, size_t* size, short x, short y, short velx, short vely){
	short i = searchParticule(liste,*size,x,y);
	if(i!=-1){
		liste[i].X = -2;
		liste[i].Y = 25;
		return;
	}
	(*size)++;
	liste = realloc(liste,(*size)*sizeof(struct Particule));
	liste[(*size)-1].X=x;
	liste[(*size)-1].Y=y;
	liste[(*size)-1].velX=velx;
	liste[(*size)-1].velY=vely;
}

void play(struct Particule* liste, size_t size, short width, short height){
    	for(size_t i = 0; i<size; i++){
    		int state = 0;
        	if(liste[i].X+liste[i].velX<=0 || liste[i].X+liste[i].velX>=width-1){
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
        
        	if(liste[i].Y+liste[i].velY<=0 || liste[i].Y+liste[i].velY>=height-1){
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
	size_t i = 0;
    	while(i<size){
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
		fputc('*',output);
		for(short j = 0; j<width; j++){
			int temp = searchParticule(liste,size,j,i);
			if(temp!=-1)
				fputc('+',output);
			else
				fputc(' ',output);
		}
		fputc('*',output);
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
    
	short width = getValue(input);
	short height = getValue(input);
	short lapNumber = getValue(input);

    if(width<1 || height<1 || width>20 || height>20){
        fputs("Error\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }
     
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

	struct Particule* liste = malloc(sizeof(struct Particule));
	size_t* size = malloc(sizeof(size_t));
	(*size) = 1;
	liste[0].X=x;
	liste[0].Y=y;
	liste[0].velX=velx;
	liste[0].velY=vely;
	
	short temp = getValue(input);
	while(temp!=-500){
		x = temp;
		y = getValue(input);
		velx = getValue(input);
		vely = getValue(input);
        	if(x<0 || x>=width || y<0 || y>=height || velx==-500 || vely==-500){
           		fputs("Error\n",output);
			free(liste);
			free(size);
            		fclose(input);
            		fclose(output);
            		return 0;
        	}
		addParticule(liste,size,x,y,velx,vely);
		temp = getValue(input);
	}
	fclose(input);
	
	for(short i = 0; i<lapNumber; i++){
		play(liste,*size,width,height);
		checkCollision(liste,*size);		
	}


	writeOutput(output,liste,*size,width,height);	
   	free(liste);
   	free(size);
	fclose(output);
		
	return 0;
}

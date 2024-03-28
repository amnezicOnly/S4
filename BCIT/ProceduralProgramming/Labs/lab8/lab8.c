#include <stdio.h>

size_t size = 0;

typedef struct Node{
	void* data;
	struct Node* next;
} Node;

int quitError(FILE* input, FILE* output){
	fputs("Error\n",output);
	fclose(output);
	fclose(input);
	return 0;
}

void freeLinkedList(Node* liste, size_t size){
	Node temp = (*liste);
	for(size_t i=0; i<size; i++){
		
	}
}

int main(int argc, char** argv){
	if(argc!=3)
		perror("Error\n");
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		perror("Error\n");
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		perror("Error\n");
	
	int type = fgetc(input)-'0';
	if(type<1 || type>5){
		return quitError(input,output);
	}
	fgetc(input);
	switch(type){
		case 1:
			size = sizeof(short);
			break;
		case 2:
			size = sizeof(int);
			break;
		case 3:
			size = sizeof(float);
			break;
		case 4:
		case 5:
			size = sizeof(char);
			break;
		default :
			quitError(input,output);
	}
	
	Node* linkedList = NULL;
	size_t size = 0;
	
	fclose(input);
	fclose(output);
    	return 0;
}

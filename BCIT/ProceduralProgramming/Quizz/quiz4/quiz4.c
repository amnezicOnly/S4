// A01410991
// Antoine Leveque
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

typedef struct Stack {
    size_t nelems;
    size_t elem_size_bytes;
    void *top;
} Stack;



Stack *stack_create(size_t elem_size_bytes) {
	Stack *s = malloc(sizeof(Stack));
	s->nelems = 0;
	s->top = NULL;
	s->elem_size_bytes = elem_size_bytes*1000;
	return s;
}


void stack_push(Stack *s, void *data,size_t size) {
    	char* name1 = (char*)data;
    	printf("Print 1: %s\n",name1);
	void *new_node = malloc(sizeof(void *) + s->elem_size_bytes);
	memcpy((char *) new_node + sizeof(void *), name1, sizeof(char)*size);
    	char* name2 = (char*)new_node;
    	printf("Print 2: %s\n",name2);
	*((void **) new_node) = s->top;
	s->top = new_node;
	s->nelems++;
}

void stack_pop(Stack *s, void *addr) {
    if (s->nelems == 0) {
        exit(1);
    }
    void *n = s->top;
    memcpy(addr, (char *) n + sizeof(void *), s->elem_size_bytes);
    s->top = *(void **) s->top;
    free(n);
    s->nelems--;
}



void writeInFile(FILE* output, Stack* stack){
	printf("File in\n");
	while(stack->nelems>1){
		char* word = malloc(100);
		stack_pop(stack,&word);
		printf("%s ",word);
		fprintf(output,"%s",word);
	}
	char* word = malloc(100);
	stack_pop(stack,&word);
	printf("%s",word);
	fprintf(output,"%s\n",word);
}

int processData(FILE* input, FILE* output){
	Stack *stack = stack_create(sizeof(char*));
	char temp;
	while((temp=fgetc(input))!='\n' && temp!=EOF){
		//printf("%c\n",temp);
		char* word = malloc(sizeof(char));
		word[0] = temp;
		size_t size = 1;
		while((temp=fgetc(input))!=' ' && temp!='\n' && temp!=EOF){
			//printf("%c\n",temp);
			word = realloc(word,(size+1)*sizeof(char));
			word[size] = temp;
			size++;
		}
		word = realloc(word,(size+1)*sizeof(char));
		word[size] = '\0';
		size++;
		//printf("%s\n",word);
		stack_push(stack,word,size);
		if(temp=='\n')
			break;
	}
	
	writeInFile(output,stack);
	return 0;
}
/*
void freeStack(Stack *stack) {
    	if (stack == NULL)
        	return;
	//printf("%s\n",stack->top->data);
    	while (stack->top != NULL) {
    		//printf("ok\n");
        	free(temp);
    	}
    	free(stack);
}*/


int main(int argc, char** argv){
	if(argc!=3){
		perror("3 arguments required\n");
	}
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		perror("Unable to open input file.\n");
		
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		perror("Unable to open output file.\n");
	//printf("Ok 0\n");
		
	
	//printf("Ok\n");
	int check = processData(input,output);
	//printf("Ok\n");
	if(check<0){
		fputs("Error in input file\n",output);
		//printf("Enter here\n");
		//freeStack(stack);
		fclose(output);
		fclose(input);
		return 0;
	}
	
	//printf("Ok\n");
	//freeStack(stack);
	fclose(output);
	fclose(input);
	
	return 0;
}

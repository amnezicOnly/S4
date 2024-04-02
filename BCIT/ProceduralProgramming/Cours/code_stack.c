#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Stack{
	size_t num_elt;
	size_t size;
	void* top;
} Stack;

Stack* create_stack(size_t taille){
	Stack* stack = malloc(sizeof(Stack));
	if(stack==NULL)
		perror("Error\n");
	stack->num_elt = 0;
	stack->size = taille;
	stack->top = NULL;
	return stack;
}

void stack_push(Stack *s, void* data){
	if(s->num_elt==0)
		s->data = malloc(s->size);
	else
		s->data = realloc(s,((s->num_elt)+1)*(s->size));
		
	if(s->data==NULL)
		perror("Error\n");
	
	s->size++;
	for(size_t i=s->size-1; i>0; i--){
		memcpy(s->top[i],s->top[i-1],s->size);
	}
	s->top[0] = data;
}

void stack_pop(Stack* s, void* dest){
	if(s->num_elt==0)
		perror("Error\n");
	
	
		
}

int main(){
	Stack* stack = create_stack();
	for(int i = 0; i<10; i++)
		stack_push(stack,&i);
	
	int temp;
	for(int i = 0; i<10; i++){
		stack_pop(stack,&temp);
		printf("Ok\n");
		printf("Pop %d from stack\n",temp);
	}

	return 0;
}

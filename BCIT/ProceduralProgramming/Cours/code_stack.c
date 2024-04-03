#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Stack{
	size_t num_elt;
	size_t size;
	void* top;
} Stack;

void stack_push(stack *s, void *data) {
	void *new_node = malloc(sizeof(void *) + s->elem_size_bytes);
	memcpy((char *) new_node + sizeof(void *),data, s->elem_size_bytes);
	*((void **) new_node) = s->top;
	s->top = new_node;
	s->nelems++;
}

void stack_pop(stack *s, void *addr) {
	if (s->nelems == 0) {
		exit(1);
	}
	void *n = s->top;
	memcpy(addr, (char *) n + sizeof(void *), s->elem_size_bytes);
	s->top = *(void **) n;
	free(n);
	s->nelems--;
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

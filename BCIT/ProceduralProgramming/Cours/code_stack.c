#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
} Node;

struct Node* temp;

void push(int val){
	Node* ptr = malloc(sizeof(Node));
	ptr->data = val;
	ptr->next = temp;
	temp = ptr;
}

int pop(){		
	int rv;
	Node* ptr;
	ptr = temp;
	rv = temp->data;
	temp = temp->next;
	free(ptr);
	return rv;
}

int main(){
	push(1);
	int data = pop();
	printf("%d\n",data);
	return 0;
}

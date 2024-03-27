#include <stdio.h>
#include <stdlib.h>

struct LinkedList{
  int data;
  struct LinkedList *next;
};

typedef struct LinkedList *node;

void createNode(node head, int value){
  node temp;
  temp = malloc(sizeof(struct LinkedList));
  temp->data = value;
  temp->next = NULL;

  node p = head;
  while(p->next != NULL){
    p = p->next;
  }
  // at the tail node
  p->next = temp;
}

void deleteNode(node head, int value){
  node prev = head;
  node curr = head->next;

  while(curr != NULL && curr->data != value){
    curr = curr->next;
    prev = prev->next;
  }
  // found a match or doesn't exit
  if(curr == NULL){ // doesn't exit
    return;
  } else { // I do have a match
    prev->next = curr->next;
    free(curr);
  }
}

void printLL(node head){
  node itr = head->next;
  while(itr != NULL){
    printf("%d ", itr->data);
    itr = itr->next;
  }
  printf("\n");
}

void deleteLL(node head){
  node prev = head;
  node curr = head->next;
  while(curr != NULL){
    free(prev);
    prev = curr;
    curr = curr->next;
  }
  free(prev);
}

int main(){
  int n = 15;
  node head;
  head = malloc(sizeof(struct LinkedList));
  head->next = NULL;

  for(int i=0; i<n; i++){
    createNode(head, i);
  }

  printLL(head);
  deleteNode(head, 9);
  printLL(head);
  deleteLL(head);

  return 0;
}

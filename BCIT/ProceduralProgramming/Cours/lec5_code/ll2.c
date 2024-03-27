#include <stdio.h>
#include <stdlib.h>

struct LinkedList{
  int data;
  struct LinkedList *next;
  struct LinkedList *prev;
};

typedef struct LinkedList *node;

void createNode(node tail, int value){
  node temp;
  temp = malloc(sizeof(struct LinkedList));
  temp->data = value;
  temp->next = NULL;

  node p = tail;

  temp->next = p;
  p->prev->next = temp;
  temp->prev = p->prev;
  p->prev = temp;
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
  while(itr->next != NULL){
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

void swapNodes(node head, node tail){
  node first = head->next;
  node second = tail->prev;
  node fnext = first->next;
  node prevs = second->prev;

  prevs->next = first;
  first->next = tail;
  first->prev = prevs;
  tail->prev = first;
  head->next = second;
  second->next = fnext;
  fnext->prev = second;
  second->prev = head;
}

int main(){
  int n = 5;
  node head, tail;
  head = malloc(sizeof(struct LinkedList));
  head->prev = NULL;
  tail = malloc(sizeof(struct LinkedList));
  tail->next = NULL;
  head->next = tail;
  tail->prev = head;
  
  for(int i=0; i<n; i++){
    createNode(tail, i);
  }

  printLL(head);
  //  deleteNode(head, 9);
  swapNodes(head->next, tail->prev);
  printLL(head);
  //  deleteLL(head);

  return 0;
}

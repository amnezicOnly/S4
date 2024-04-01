#include <stdio.h>
//#include <stdlib.h>
//#include <err.h>
//#include <string.h>

// J'ai eu 7/9

typedef struct SkipList{
    // the data in the current node
    int data;
    // the next node in the linked list
    struct SkipList* next;
    // the same node but on the level under this one
    struct SkipList* under;
}  SkipList;

int skipList_search(SkipList* liste, int element){
    if(liste==NULL)
        return -1;

    int res = -1;
    SkipList* current = liste;
    while(res==-1){
        // while next node exists and its data strictly inferior to the current one
        while(current->next!=NULL && current->next->data < element)
            current = current->next;
        // if we found the element we are looking for
        if(current->data = element)
            return element;

        // otherwise, if there is no next node on the same level nor level under the current one
        // that is to say that element isn't here
        if((current->next==NULL || current->next->data > element) && current->under==NULL)
            return -1;

        // otherwise, the next node doesn't exist or its data is strictly superior than the element we are looking for
        // and there is a level under the current one, so we go there
        current = current->under;
    }
    return res;
}


int main(int argc, char** argv){
    SkipList* liste = NULL;
    int res = skipList_search(liste,5);
    printf("res = %d\n",res);
	return 0;
}

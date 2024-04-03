#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a generic structure for nodes in the linked list
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Function to create a new node
Node* newNode(void *data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to merge two sorted linked lists
Node* merge(Node* left, Node* right, int (*cmp)(void*, void*)) {
    Node* result = NULL;
    
    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;
    
    if (cmp(left->data, right->data) <= 0) {
        result = left;
        result->next = merge(left->next, right, cmp);
    } else {
        result = right;
        result->next = merge(left, right->next, cmp);
    }
    
    return result;
}

// Function to split the linked list into two halves
void split(Node* head, Node** left, Node** right) {
    if (head == NULL || head->next == NULL) {
        *left = head;
        *right = NULL;
    } else {
        Node* slow = head;
        Node* fast = head->next;
        
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        
        *left = head;
        *right = slow->next;
        slow->next = NULL;
    }
}

// Merge sort function
void mergeSort(Node** head, int (*cmp)(void*, void*)) {
    if (*head == NULL || (*head)->next == NULL)
        return;
    
    Node* left;
    Node* right;
    split(*head, &left, &right);
    
    mergeSort(&left, cmp);
    mergeSort(&right, cmp);
    
    *head = merge(left, right, cmp);
}

// Comparison function for integers
int intCompare(void *a, void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to print an integer
void printInt(void *data) {
    printf("%d ", *(int*)data);
}

// Function to free the memory allocated for the linked list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(Node* head, void (*printFunc)(void*)) {
    while (head != NULL) {
        printFunc(head->data);
        printf(" ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    
    // Example data
    int a = 5;
    int b = 2;
    int c = 7;
    int d = 1;
    int e = 9;
    
    // Insert data into linked list
    head = newNode(&a);
    head->next = newNode(&b);
    head->next->next = newNode(&c);
    head->next->next->next = newNode(&d);
    head->next->next->next->next = newNode(&e);
    
    // Sort the linked list
    mergeSort(&head, intCompare);
    
    // Print the sorted linked list
    printList(head, printInt);
    
    // Free the memory allocated for the linked list
    freeList(head);
    
    return 0;
}




/*
Now, instead of adding manually element on the linked list with a, b, c, d and e, you have to read a file in this way :
the first line contains a number between 1 and 5 included
the second line contains text
the thrird line only contains the letter 'E'

*/

// A0140991
// Antoine Leveque

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

size_t size;
char type;
FILE* input;
FILE* output;

typedef struct Node{
	void* data;
	struct Node* next;
} Node;

int compareNumbers(char* word1, char* word2){
	if(type=='3'){
		int negative1 = 0;
		if(word1[0]=='-')
			negative1++;
		int negative2 = 0;
		if(word2[0]=='-')
			negative2++;
		float num1 = strtof(word1+negative1, NULL);
		float num2 = strtof(word2+negative2, NULL);
		if(word1[0]=='-')
			num1*=(-1);
		if(word2[0]=='-')
			num2*=(-1);
		if(num1<num2)
			return -1;
		return 1;
	}
	int negative3 = 0;
	if(word1[0]=='-')
		negative3++;
	int negative4 = 0;
	if(word2[0]=='-')
		negative4++;
	long int num3 = strtol(word1+negative3,NULL,20);
	long int num4 = strtol(word2+negative4,NULL,20);
	if(word1[0]=='-')
		num3*=(-1);
	if(word2[0]=='-')
		num4*=(-1);
	if(num3<num4)
		return -1;
	return 1;
}


int compare(void* word1, void* word2){
	char* text1 = (char*)word1;
	char* text2 = (char*)word2;
	if(type=='1' || type=='2' || type=='3'){
		return compareNumbers(text1,text2);
	} else {
		size_t i = 0;
		while(text1[i]!='\0' && text2[i]!='\0' && text1[i]==text2[i])
			i++;
		if(text1[i]=='\0' && text2[i]!='\0')
			return -1;
		if(text1[i]!='\0' && text2[i]=='\0')
			return 1;
		if(text1[i]!='\0' && text2[i]!='\0' && text1[i]<text2[i])
			return -1;
		if(text1[i]!='\0' && text2[i]!='\0' && text1[i]<text2[i])
			return 1;
		return 0;
	}
}

Node* merge(Node* list1, Node* list2) {
    	if (list1 == NULL)
    		return list2;
    	if (list2 == NULL)
    		return list1;

    	Node* result = NULL;
    	Node* current = NULL;

    	while (list1 != NULL && list2 != NULL) {
		if(compare(list1->data,list2->data)<0){
            		if (result == NULL) {
                		result = list1;
                		current = list1;
            		} else {
               			 current->next = list1;
                		current = current->next;
           		}
           		list1 = list1->next;
        	} else {
            		if (result == NULL) {
                		result = list2;
               			current = list2;
            		} else {
                		current->next = list2;
                		current = current->next;
            		}
            		list2 = list2->next;
        	}
    	}

    	if (list1 != NULL) {
        	current->next = list1;
    	} else {
        	current->next = list2;
    	}
    	return result;
}


void splitList(Node* head, Node** left, Node** right) {
    	Node* fast;
    	Node* slow;
    	
    	if (head == NULL || head->next == NULL) {
        	*left = head;
        	*right = NULL;
    	} else {
        	slow = head;
        	fast = head->next;

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

// Fonction principale de tri fusion
void mergeSort(Node** linkedList) {
	Node* head = *linkedList;
	
	Node* a;
	Node* b;
	
	if (head == NULL || head->next == NULL) {
		return;
	}

	splitList(head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*linkedList = merge(a, b);
}

int checkShort(char* source, int negative) {
	char str[strlen(source) + 1];
	sprintf(str, "%hd", ((short)atoi(source+negative)));
	if(strcmp(str, source+negative) == 0)
		return 1;
	return -1;
}

int checkInt(char* source, int negative) {/*
    	char* endptr;
    	long num = strtol(str+negative, &endptr, 20);
    	if (endptr == str || *endptr != '\0') {
    	    return -1;
    	}

    	if (num < INT_MIN || num > INT_MAX) {
    	    return -1;
    	}
	return 1;*/
	
	char str[strlen(source) + 1];
	sprintf(str, "%d", atoi(source+negative));
	if(strcmp(str, source+negative) == 0)
		return 1;
	return -1;
}

int checkFloat(char* str, int negative) {
    	char* endptr;
    	float num = strtof(str+negative, &endptr);
    	if (endptr == str || *endptr != '\0') {
        	return -1;
    	}

    	if (num < -FLT_MAX || num > FLT_MAX) {
        	return -1;
    	}

    	return 1;
}


void addData(Node** liste, void *dataptr, size_t size) {
   	Node *newNode = (Node*)malloc(sizeof(Node));
    	if (newNode == NULL) {
        	exit(EXIT_FAILURE);
    	}

    	newNode->data = malloc(size);
	memcpy(newNode->data, dataptr, size);
    	newNode->next = *liste;
    	*liste = newNode;
}

void writeInFile(Node* linkedList){
	Node* curr = linkedList;
	while(curr!=NULL){
		fprintf(output,"%s",(char*)curr->data);
		if(curr->next!=NULL)
			fprintf(output,",");
		curr = curr->next;
	}
	fprintf(output,"\n");
}

int fileProcess(Node** linkedList){
	char temp;
	while((temp=fgetc(input))!='\n' && temp!=EOF){
		int virgule = 0;
		char* word = malloc(sizeof(char));
		word[0] = temp;
		int negative = 0;
		if(temp=='-')
			negative++;
		size_t size = 1;
		while((temp=fgetc(input))!=',' && temp!='\n' && temp!=EOF){
			if(type<='3' && temp=='-'){
				return -1;
			}
			if(temp=='.'){
				if(virgule!=0)
					return -1;
				virgule++;
			}
			word = realloc(word,(size+1)*sizeof(char));
			word[size] = temp;
			size++;
		}
		if((type=='4' && size!=1)||(type>='1' && type<='3' && size>=20))
			return -1;

		if(type=='1' && checkShort(word,negative)<0){
			return -1;
		}
		if(type=='2' && checkInt(word,negative)<0){
			return -1;
		}
		if(type=='3' && (virgule!=1 ||checkFloat(word,negative)<0)){
			return -1;
		}
		addData(linkedList,word,size);

		if(temp=='\n')
			break;
		}
	return 0;
}

void freeLinkedList(Node* linkedList){
	Node* curr = linkedList;
	Node* next;
	
	while(curr!=NULL){
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
}

int quitProgram(Node* linkedList){
	freeLinkedList(linkedList);
    	fclose(output);
    	fclose(input);
    	return 0;
}

int quitError(Node* linkedList){
    	fputs("Error\n",output);
    	return quitProgram(linkedList);
}

int main(int argc, char** argv){
	// Bon nombre d'arguments
	if(argc!=3)
		perror("Error\n");
	
	// Gestion des fichiers
	input = fopen(argv[1],"r");
	if(input==NULL)
		perror("Error: unable to open input file\n");
	output = fopen(argv[2],"w");
	if(output==NULL)
		perror("Error: unable to open output file\n");
	
	Node* linkedList = NULL;
	
	// Récupération du type de données
	type = fgetc(input);
	if(type<'1' || type>'5'){
		return quitError(linkedList);
	}
	// Si c'est un nombre et pas un chiffre
	if (fgetc(input)!='\n'){
        return quitError(linkedList);
    }

	switch(type){
		case '1':
			size = sizeof(short);
			break;
		case '2':
			size = sizeof(int);
			break;
		case '3':
			size = sizeof(float);
			break;
		case '4':
			size = sizeof(char);
			break;
		case '5':
			size = sizeof(char*);
			break;
		default :
			return quitError(linkedList);
	}
	int check = fileProcess(&linkedList);
	if(check<0){
		return quitError(linkedList);
	}

	mergeSort(&linkedList);
	writeInFile(linkedList);
	return quitProgram(linkedList);
}

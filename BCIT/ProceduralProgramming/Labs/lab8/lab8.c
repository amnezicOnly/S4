// A0140991
// Antoine Leveque

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

/*
Mes questions :
	- Si un élément est déjà dans la liste : on l'ajoute, on ne fait rien ou erreur ?
	- 
*/

size_t size;
char type;
FILE* input;
FILE* output;

typedef struct Node{
	void* data;
	struct Node* next;
} Node;

void printList(Node* head){
	Node* curr = head;
	while(curr!=NULL){
		char* word = (char*) curr->data;
		printf("%s,",word);
		curr = curr->next;
	}
	printf("\n");
}

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

// Fonction pour fusionner deux listes triées
Node* merge(Node* list1, Node* list2) {
	//printf("Left: ");
	//printList(list1);
	//printf("Right: ");
	//printList(list2);
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    Node* result = NULL;
    Node* current = NULL;

    while (list1 != NULL && list2 != NULL) {
	if(compare(list1->data,list2->data)<0){	// si list1->data<=list2->data
            if (result == NULL) {
                result = list1;
                current = list1;
            } else {
                current->next = list1;
                current = current->next;
            }
			// on avance le 
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
    
    //printf("Result :");
    //printList(result);

    return result;
}

// Fonction pour diviser la liste en deux moitiés
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

int checkShort(char* str, int negative) {
    	char* endptr;
    	long num = strtol(str+negative, &endptr, 20);
    	if (endptr == NULL || *endptr != '\0') {
        	return -1; // La chaîne ne représente pas un nombre valide
    	}

    	if (num < SHRT_MIN || num > SHRT_MAX) {
    		//printf("erreur là\n");
        	return -1; // Le nombre dépasse la plage des shorts
    	}
	return 1; // Le nombre est un short valide dans la plage autorisée
}

int checkInt(char* str, int negative) {
    	char* endptr;
    	long num = strtol(str+negative, &endptr, 20);
    	if (endptr == str || *endptr != '\0') {
    	    return -1; // La chaîne ne représente pas un nombre valide
    	}

    	if (num < INT_MIN || num > INT_MAX) {
    	    return -1; // Le nombre dépasse la plage des int
    	}
	return 1; // Le nombre est un int valide dans la plage autorisée
}

int checkFloat(char* str, int negative) {
    char* endptr;
    float num = strtof(str+negative, &endptr);
    if (endptr == str || *endptr != '\0') {
        return -1; // La chaîne ne représente pas un nombre valide
    }

    if (num < -FLT_MAX || num > FLT_MAX) {
        return -1; // Le nombre dépasse la plage des floats
    }

    return 1; // Le nombre est un float valide dans la plage autorisée
}


void addData(Node** liste, void *dataptr, size_t size) {
    	// Création d'un nouveau nœud
   	Node *newNode = (Node*)malloc(sizeof(Node));
    	if (newNode == NULL) {
        // Gérer l'échec de l'allocation
        	exit(EXIT_FAILURE);
    	}

	
    
    	// Affectation de la donnée pointée par dataptr au nouveau noeud
    	newNode->data = malloc(size);
	memcpy(newNode->data, dataptr, size);
    	newNode->next = *liste;
    	*liste = newNode;
}

void writeInFile(Node* linkedList){
	Node* curr = linkedList;
	while(curr->next!=NULL){
		Node* next = curr->next;
		char* word = (char*)curr->data;
		fprintf(output,"%s,",word);
		curr = next;
	}
	char* word = (char*)curr->data;
	fprintf(output,"%s\n",word);
}

int fileProcess(Node** linkedList){
	char temp;
	while((temp=fgetc(input))!='\n' && temp!=EOF){
		int negative = 0;
		int virgule = 0;
		char* word = malloc(sizeof(char));
		word[0] = temp;
		size_t size = 1;
		while((temp=fgetc(input))!=',' && temp!='\n' && temp!=EOF){
			if(temp=='-'){
				if(negative!=0)
					return -1;
				negative++; 
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
		//printf("%s\n",word);
		if((type=='4' && size!=1)||(type>='1' && type<='3' && size>=20))
			return -1;

		if(type=='1' && checkShort(word,negative)<0){
			//printf("Error checkShort\n");
			//printf("%s\n",word);
			return -1;
		}
		if(type=='2' && checkInt(word,negative)<0){
			//printf("Error checkInt\n");
			return -1;
		}
		if(type=='3' && checkFloat(word,negative)<0){
			//printf("Error checkFloat\n");
			return -1;
		}
		addData(linkedList,word,size);

		if(temp=='\n')
			break;
		}
	return 0;
}

int quitProgram(){
    fclose(output);
    fclose(input);
    return 0;
}

int quitError(){
    fputs("Error\n",output);
    return quitProgram(input,output);
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
		//printf("Mauvais type: %c (1)\n",type);
		return quitError(input,output);
	}
	// Si c'est un nombre et pas un chiffre
	if (fgetc(input)!='\n'){
        //printf("Type trop grand\n");
        return quitError();
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
		default :	// si type
			//printf("Mauvais type: %c (2)\n",type);
			return quitError();
	}
	int check = fileProcess(&linkedList);
	if(check<0){
		return quitError();
	}

	mergeSort(&linkedList);
	writeInFile(linkedList);
	return quitProgram();
}

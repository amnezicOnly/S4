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


int compare(void* word1, void* word2){
	char* text1 = (char*)word1;
	char* text2 = (char*)word2;
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
void splitList(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

// Fonction principale de tri fusion
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    if (head == NULL || head->next == NULL) {
        return;
    }

    splitList(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = merge(a, b);
}

int checkShort(const char* word) {
    long long number = strtoll(word, NULL, 10); // Convertir la chaîne en nombre entier long
    if (number >= SHRT_MIN && number <= SHRT_MAX) {
        return 1; // Le nombre est dans la plage des shorts
    } else {
        return -1; // Le nombre n'est pas dans la plage des shorts
    }
}


int checkInt(char* word){
	char* endptr;
    	long int number = strtol(word, &endptr, 10); // Convertir la chaîne en entier

    	if (endptr == word) {
        	return -1;
    	}

	char buffer[20];
   	snprintf(buffer, sizeof(buffer), "%ld", number);

    	if (strcmp(word, buffer) == 0 && number>=INT_MIN && number<=INT_MAX) {
        	return 1;
    	} else {
        	return -1;
    	}
}

int checkFloat(const char* word) {
    	char* endptr;
    	float number = strtof(word, &endptr); // Convertir la chaîne en float

    	// Vérifier si la conversion a échoué
    	if (endptr == word) {
    		printf("Erreur ici\n");
        	return -1;
    	}

    	// Convertir le float en chaîne de caractères pour la comparaison
    	char buffer[20];
    	snprintf(buffer, sizeof(buffer), "%f", number);

    	// Comparer les deux chaînes
    	if (strcmp(word, buffer) == 0 && (number > -FLT_MAX && number <= FLT_MAX)){
        	return 1;
    	}
	printf("Erreur là\n");
    	return -1; // La conversion a échoué ou les chaînes ne correspondent pas
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
		if((type=='4' && size!=1)||(type>='1' && type<='3' && size>=20))
			return -1;

		if(type=='1'){
			if(checkShort(word)<0){
				printf("Error checkShort\n");
				return -1;
			}
		}
		if(type=='2'){
			if(checkInt(word)<0){
				printf("Error checkInt\n");
				return -1;
			}
		}
		if(type=='3'){
			if(virgule!=1 || checkFloat(word)<0){
				printf("Error checkFloat\n");
				return -1;
			}
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

	// ERROR
	mergeSort(&linkedList);
	writeInFile(linkedList);
	return quitProgram();
}

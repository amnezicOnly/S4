#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Mes questions :
	- Si un élément est déjà dans la liste : on l'ajoute, on ne fait rien ou erreur ?
	- 
*/



size_t size;
char type;

typedef struct Node{
	void* data;
	struct Node* next;
} Node;

// Compare data1ptr et data2ptr
int greaterThan(void* data1ptr, void* data2ptr){
    	// return :
	//	- 1 if data1ptr>data2ptr
	//	- 0 if data1ptr==data2ptr
	//	- -1 if data1ptr<data2ptr
	if(type!=5){	// if the data is numeric
		if(data1ptr>data2ptr)
			return 1;
		else if (data1ptr==data2ptr)
			return 0;
		else
			return -1;
	} else {	// if data is a String
		size_t i = 0;
        	char* text1 = (char*)data1ptr;
        	char* text2 = (char*)data2ptr;
        	int res = 0;
		while(text1[i]!='\0' && text2[i]!='\0' && text1[i]==text2[i])
			i++;
		if(text1[i]!='\0' && text2[i]=='\0')
			res = -1;
		else if(text1[i]=='\0' && text2[i]!='\0')
			res = 1;
		else if(text1[i]!='\0' && text2[i]!='\0' && text1[i]>text2[i])
			res = 1;
		else if(text1[i]!='\0' && text2[i]!='\0' && text1[i]<text2[i])
			res = -1;
		else
			res = 0;
		free(text1);
		free(text2);
		return res;		
	}
}

/*
// Fonction de tri fusion (merge sort) pour une liste chaînée
Node* mergeSort(Node *head) {
    	// Cas de base : si la liste est vide ou ne contient qu'un seul élément
    	if (head == NULL || head->next == NULL) {
        	return head;
    	}

    	// Diviser la liste en deux moitiés
    	Node *left;
    	Node *right;
    	splitList(head, &left, &right);

    	// Trier récursivement les deux moitiés
    	left = mergeSort(left);
   	right = mergeSort(right);

    	// Fusionner les deux moitiés triées
    	return merge(left, right);
}

// Fonction pour diviser la liste en deux moitiés
void splitList(Node *head, Node **left, Node **right) {
    	Node *slow = head;
    	Node *fast = head->next;

    	// Parcourir la liste avec deux pointeurs : un qui avance d'un nœud à la fois et un qui avance de deux nœuds à la fois
    	while (fast != NULL) {
        	fast = fast->next;
       		if (fast != NULL) {
            		slow = slow->next;
            		fast = fast->next;
        	}
   	}

    	// 'slow' est maintenant au milieu de la liste, divisez-la en deux parties
    	*left = head;
    	*right = slow->next;
    	slow->next = NULL;
}

// Fonction pour fusionner deux listes triées
Node* merge(Node *left, Node *right) {
    	Node *result = NULL;

    	// Cas de base : si l'une des deux listes est vide
    	if (left == NULL) {
        	return right;
    	} else if (right == NULL) {
        	return left;
    	}

    	// Comparer les valeurs des deux listes et fusionner les nœuds en ordre
    	int status = greaterThan(left->data, right->data);
    	if (status<=0) {
        	result = left;
        	result->next = merge(left->next, right);
    	} else {
        	result = right;
        	result->next = merge(left, right->next);
   	}

    	return result;
}*/

// Écrit la liste finale dans le fichier
void putInFile(FILE* output, Node* linkedList){
	Node *current = linkedList;
    	Node *next;
    	
    	// pour chaque élément
    	while (current->next != NULL) {
    		// en fonction du type on choisit un % différent
    		switch(type){
	    		case '1':
		        short value1 = *((short*)current->data); 
				    fprintf(output,"%u,",value1);
	    		case '2':
		        int value2 = *((int*)current->data);
				    fprintf(output,"%d,",value2);
	    		case '3':
		        float value3 = *((float*)current->data);
			    	fprintf(output,"%f,",value3);
	    		case '4':
		        char value4 = *((char*)current->data);
				    fprintf(output,"%c,",value4);
	    		case '5':
		        char* value5 = ((char*)current->data);
				    fprintf(output,"%s,",value5);
	    		default:
		           break;
	    	}
		next = current->next;
		current = next;      // Passer au noeud suivant
   	}
    	
    // autre manière de faire
   	/*
	switch(type){
		case '1':	// short
			while (current->next != NULL) {
    				fprint(output,"%zu,"current->data);
        			next = current->next;
        			free(current->data); // Libérer la mémoire allouée pour les données
        			free(current);       // Libérer la mémoire allouée pour le noeud
        			current = next;      // Passer au noeud suivant
    			}
    			break;
		case '2':	// int
			while (current->next != NULL) {
    				fprint(output,"%d,"current->data);
        			next = current->next;
        			free(current->data); // Libérer la mémoire allouée pour les données
        			free(current);       // Libérer la mémoire allouée pour le noeud
        			current = next;      // Passer au noeud suivant
    			}
    			break;
		case '3':	// float
			while (current->next != NULL) {
    				fprint(output,"%f,"current->data);
        			next = current->next;
        			free(current->data); // Libérer la mémoire allouée pour les données
        			free(current);       // Libérer la mémoire allouée pour le noeud
        			current = next;      // Passer au noeud suivant
    			}
    			break;
		case '4':	// char
			while (current->next != NULL) {
    				fprint(output,"%c,"current->data);
        			next = current->next;
        			free(current->data); // Libérer la mémoire allouée pour les données
        			free(current);       // Libérer la mémoire allouée pour le noeud
        			current = next;      // Passer au noeud suivant
    			}
    			break;
		case '5':	// String
			// à gérer
    			break;
		default:
			printf("Error: putInFile type: %c\n",type);
			break;
	}*/
}

void freeLinkedList(Node* linkedList){
    Node *current = linkedList;
    Node *next;
    	
    while (current->next != NULL) {
	    next = current->next;
	    free(current->data); // Libérer la mémoire allouée pour les données
	    free(current);       // Libérer la mémoire allouée pour le noeud
	    current = next;      // Passer au noeud suivant
    }
    free(current->data);
    free(current);
}

int fileProcess(FILE* input, Node* linkedList){
	return 0;
}

int quitProgram(FILE* input, FILE* output){
    fclose(output);
    fclose(input);
    return 0;
}

int quitError(FILE* input, FILE* output){
    fputs("Error\n",output);
    return quitProgram(input,output);
}

int main(int argc, char** argv){
	// Bon nombre d'arguments
	if(argc!=3)
		perror("Error\n");
	
	// Gestion des fichiers
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		perror("Error: unable to open input file\n");
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		perror("Error: unable to open output file\n");
	
	Node* linkedList = NULL;
	
	// Récupération du type de données
	type = fgetc(input);
	if(type<'1' || type>'5'){
		printf("Mauvais type: %c (1)\n",type);
		return quitError(input,output);
	}
	if (fgetc(input)!='\n'){
        	printf("Type trop grand\n");
        	return quitError(input,output);
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
		case '5':
			size = sizeof(char);
			break;
		default :	// si type
			printf("Mauvais type: %c (2)\n",type);
			return quitError(input,output);
	}
	// if there is any problem with the file
	int processStatus = fileProcess(input,linkedList);
	if(processStatus!=0){
        	freeLinkedList(linkedList);
		return quitError(input,output);
   	}
		
	// sort the linked list by merge sort
	// linkedList = mergeSort(linkedList);
	
	// wrote data into the output file
	putInFile(output,linkedList);
	
    	// on free la liste chaînée correctement
    	freeLinkedList(linkedList);

	// close files and quit the program
	return quitProgram(input,output);
}

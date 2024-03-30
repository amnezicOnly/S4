#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de l'élément de la liste chaînée
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Variables globales pour stocker le type et la taille
char type;
size_t size;

// Fonction pour lire le fichier et remplir la liste chaînée
Node* readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    // Lecture du type et détermination de la taille
    fscanf(file, "%c", &type);
    switch (type) {
        case '1': size = sizeof(short); break;
        case '2': size = sizeof(int); break;
        case '3': size = sizeof(float); break;
        case '4': size = sizeof(char); break;
        case '5': size = sizeof(char*); break;
        default:
            fprintf(stderr, "Type non reconnu.\n");
            exit(EXIT_FAILURE);
    }

    // Lecture des éléments et création de la liste chaînée
    char buffer[1000];
    fscanf(file, "%s", buffer); // Lecture de la deuxième ligne
    Node *head = NULL;
    char *token = strtok(buffer, ",");
    while (token != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->data = malloc(size);
        memcpy(newNode->data, token, size);
        newNode->next = head;
        head = newNode;
        token = strtok(NULL, ",");
    }

    // Vérification de la troisième ligne
    char c;
    fscanf(file, " %c", &c); // Lecture de la troisième ligne
    if (c != 'E') {
        fprintf(stderr, "Format de fichier incorrect.\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return head;
}

// Fonction pour afficher les éléments de la liste chaînée
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        switch (type) {
            case '1': printf("%d ", *(short*)current->data); break;
            case '2': printf("%d ", *(int*)current->data); break;
            case '3': printf("%f ", *(float*)current->data); break;
            case '4': printf("%c ", *(char*)current->data); break;
            case '5': printf("%s ", *(char**)current->data); break;
        }
        current = current->next;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire allouée pour la liste chaînée
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main() {
    Node *head = readFile("input.txt");

    // Ici, vous pouvez trier la liste avec Merge Sort

    printf("Liste triée :\n");
    printList(head);

    freeList(head);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// update this with your A number
char a_num[] = "";

struct ListNode
{
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode *head)
{
    int is_palindrome = true;
    // WRITE YOUR CODE HERE
	size_t size = 0;
	struct ListNode* temp = head;
	while(temp!=NULL){
		size++;
		temp = temp->next;
	}
	
	int res = 0;
	temp = head;
	if(size%2==1){
		for(size_t i = 0; i<size/2; i++){
			res+=temp->val;
			temp = temp->next;
		}
		temp = temp->next;
		for(size_t i = (size/2)+1; i<size; i++){
			res-=temp->val;
			temp = temp->next;
		}
	}
	else{
		for(size_t i = 0; i<size/2; i++){
			res+=temp->val;
			temp = temp->next;
		}
		for(size_t i = size/2; i<size; i++){
			res-=temp->val;
			temp = temp->next;
		}
	}
	
	if(res!=0)
		is_palindrome = false;
		
    // DONT EDIT ANYTHING BELOW THIS LINE
    return is_palindrome;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    struct ListNode *head = NULL;

    // Read the input linked list from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    // Read the input linked list node by node until encountering "E"
    int val;
    char inputChar;
    while ((inputChar = fgetc(file)) != 'E')
    {
        if (inputChar >= '0' && inputChar <= '9')
        {
            ungetc(inputChar, file);  // Put the digit back into the stream
            fscanf(file, "%d", &val); // Read the integer value
            printf("value is %d\n", val);
            // Create a new node
            struct ListNode *new_node = (struct ListNode *)malloc(sizeof(struct ListNode));
            if (new_node == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }
            new_node->val = val;
            new_node->next = NULL;

            // Append the new node to the linked list
            if (head == NULL)
            {
                head = new_node;
            }
            else
            {
                struct ListNode *temp = head;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = new_node;
            }
        }
    }

    fclose(file);
    printf("A%s\n", a_num);

    // Check if the linked list is a palindrome
    bool result = isPalindrome(head);

    // Output the result to the file
    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening file for writing.\n");
        return 1;
    }

    fprintf(output_file, "%s\n", result ? "true" : "false");

    // Close the file
    fclose(output_file);

    // Free the memory allocated for the linked list nodes
    while (head != NULL)
    {
        struct ListNode *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

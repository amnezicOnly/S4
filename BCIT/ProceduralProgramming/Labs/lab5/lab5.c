#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Update this with your A number
char a_num[] = "01410991";



void zoomArray(char*** arr, float n, int *rows, int *cols){
	int new_rows = (*rows)*n;
    	int new_cols = new_rows;
    	char** temp = *arr;
    	if(n>1){    // agrandissement de arr        	
    		temp = (char**)realloc(temp,new_rows*sizeof(char*));
        	for(int i = (*rows); i<new_rows; i++)
            		temp[i] = 0;
        	for(int i=0; i<new_rows; i++){
            		if(temp[i]==NULL){
                		temp[i] = (char*)malloc(new_cols*sizeof(char));
            		}
            		else{
                		temp[i] = (char*)realloc(temp[i],new_cols*sizeof(char));
            		}
        	}
        
        	if(new_rows%2==1){	// longueur impaire
			for(int i=new_rows-1; i>=0; i--){
            			int line = i/((*rows)-1);
            			for(int j=new_cols-1; j>=0; j--){
               				temp[i][j] = temp[line][j/((*cols)-1)];
            			}
        		}
		}
	
		else{
			for(int i=new_rows-1; i>=0; i--){
            			int line = i/(*rows);
            			for(int j=new_cols-1; j>=0; j--){
               				temp[i][j] = temp[line][j/(*cols)];
            			}
        		}
		}
	}
	
	if(n<1){
								
	}
	
		
	(*rows) = new_rows;
	(*cols) = new_cols;
	*arr = temp;
}

int main(int argc, char *argv[]){
	if (argc != 3)
    	{
        	printf("Usage: %s <input_file> <output_file\n", argv[0]);
        	return 1;
    	}

    	char *inputFileName = argv[1];
    	int dimensions = 0;
    	char **arr = NULL;
    	int rows = 0, cols = 0;
    	float zoomFactor = 0;
    
    	// Read the input array from the specified file
    	FILE *file = fopen(inputFileName, "r");
    	if (file == NULL){
        	perror("Error opening input file");
        	return 1;
    	}

    	// Read the row value
    	fscanf(file, "%d", &rows);
    	// Read the column value
    	fscanf(file, "%d", &cols);
    	// Read the zoom factor
    	fscanf(file, "%f", &zoomFactor);

    	// Allocate memory for the 2D array
    	arr = (char **)malloc(rows * sizeof(char *));
    	if (arr == NULL){
        	printf("Memory allocation failed.\n");
        	return 1;
    	}
    	for (int i = 0; i < rows; i++){
        	arr[i] = (char *)malloc(cols * sizeof(char));
        	if (arr[i] == NULL){
            		printf("Memory allocation failed.\n");
            		return 1;
        	}
    	}

    	// Read the elements of the array until 'E' is encountered
    	char inputChar;
    	int i = 0, j = 0;
    	while ((inputChar = fgetc(file)) != 'E'){
        	if (inputChar >= '0' && inputChar <= '9' && i < rows && j < cols){
            		arr[i][j++] = inputChar;
            		if (j == cols){
                		j = 0;
                		i++;
            		}
        	}
    	}

    	fclose(file);
    	printf("A%s\n", a_num);


    	// Output the input array
    	printf("Input Array:\n");
    	for (int i = 0; i < rows; i++){
        	for (int j = 0; j < cols; j++){
            		printf("%c", arr[i][j]);
        	}
        	printf("\n");
    	}
    	printf("\n");

    	// Call the zoomArray function
    	zoomArray(&arr, zoomFactor, &rows, &cols);
    
    
    	FILE* output = fopen(argv[2],"w");
    	if(output==NULL){
        	perror("Error opening output file");
        	return 1;
    	}
    
    	for(int i=0; i<rows-1; i++){
		for(int j=0; j<cols; j++){
	    		fputc(arr[i][j],output);
		}
  		fputc('\n',output);
    	}
    	for(int i=0; i<cols; i++)
    		fputc(arr[rows-1][i],output);    	

    	fclose(output);
    
    	// Free the memory allocated for the 2D array
    	for (int i = 0; i < rows; i++){
        	free(arr[i]);
	}
    	free(arr);

    	return 0;
}

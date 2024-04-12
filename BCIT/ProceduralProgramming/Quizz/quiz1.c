#include <stdio.h>
#include <stdlib.h>

// update this with your A number
char a_num[] = "";

void transposeArray(int arr[10][10], int rows, int cols) {
	for(int i=0; i<rows; i++){
		for(int j=i; j<cols; j++){
			int temp = arr[i][j];
			arr[i][j]=arr[j][i];
			arr[j][i] = temp;
		}
	}		

    // Do NOT write any code below
    // Output the transposed array
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the transposed array to the file
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            fprintf(file, "%d", arr[i][j]);
        }
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int dimensions = 0;
    int arr[10][10] = {0};  // Initialize the array with zeros
    int rows = 0, cols = 0;
    char inputChar;

    // Read the input array from the specified file
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the first line for array dimensions
    fscanf(file, "%d", &dimensions);
    // Read the input array character by character
    int counter = 0; //To skip first line in the file
    while (rows < 10 && (inputChar = fgetc(file)) != 'E') {
        if (inputChar == '\n'){counter++;}
        if (inputChar == '\n' && counter > 1){
            rows++;
            cols = 0;
        } else if (cols < 10 && inputChar >= '0' && inputChar <= '9') {
            arr[rows][cols++] = inputChar - '0';
        }
    }

    fclose(file);
    printf("A%s\n", a_num);
    // Actual dimensions of the input array
    rows = cols = dimensions;

    transposeArray(arr, rows, cols);

    return 0;
}

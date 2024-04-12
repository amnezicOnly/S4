#include <stdio.h>
#include <stdlib.h>

// update this with your A number
char a_num[] = "01410991";

void rotateArray(int arr[10][10], int n, int rows, int cols) {
    int check = n%90;
    if (rows<1 || rows>10 || cols<1 || cols>10 || check!=0)
        // check if there are at most 10 lines/columns and if n is a multiple of 90
        printf("There is a problem with the arguments.\n");
   

   // Circles are 2-PI periodic 
    int nbRotations = n/90;
    if(n<0)
        nbRotations%=-4;
    else
        nbRotations%=4;

    int second[10][10] = {0};
    for(int i=0;i<rows;i++){
    	for(int j=0;j<cols;j++){
    		second[i][j]=arr[i][j];
    	}
    }

    int Rindex = rows-1;
    int Cindex = cols-1;
    if(nbRotations==2 || nbRotations==-2){
        for(int i=0; i<rows/2; i++){
            for(int j=0;j<cols;j++){
                int temp = arr[i][j];
                arr[i][j] = arr[Rindex-i][Cindex-j];
                arr[Rindex-i][Cindex-j] = temp;
            }
        }
        int middle = rows/2;
        for(int j=0;j<cols/2;j++){
            int temp = arr[middle][j];
            arr[middle][j]=arr[middle][Cindex-j];
            arr[middle][Cindex-j] = temp;
        }
    }
    

    else if (nbRotations==1||nbRotations==-3){
        for(int i=0; i<rows; i++){
            for(int j=0;j<cols;j++){
                arr[i][j] = second[Cindex-j][i];
            }
        }
    }
    
    else if(nbRotations==-1||nbRotations==3){
        for(int i=0; i<rows; i++){
            for(int j=0;j<cols;j++){
                arr[i][j] = second[j][Rindex-i]; 

            }
        }
    }
    
    else{   // case n=360 so no rotation
    }

    // Do NOT write any code below
    // Output the rotated array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file> <input_angle_degrees>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int rotationAngle = 0;
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

    // Read the first line for angle of rotation and second line for array dimensions
    fscanf(file, "%d", &rotationAngle);
    fscanf(file, "%d", &dimensions);
    // Read the input array character by character
    int counter = 0; //To skip first two lines in the file
    while (rows < 10 && (inputChar = fgetc(file)) != 'E') {
        if (inputChar == '\n'){counter++;}
        if (inputChar == '\n' && counter>=2) {
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

    printf("Input array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
	    if(arr[i][j] == 0)
	      printf(" ");
	    else
	      printf("%d", arr[i][j]);
        }
        printf("\n");
    }

    printf("\nRotated array (%d degrees):\n", rotationAngle);
    rotateArray(arr, rotationAngle, rows, cols);

    return 0;
}

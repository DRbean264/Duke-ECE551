#include <stdio.h>
#include <stdlib.h>

#define MATRIXSIZE 10

void rotateMatrix(char matrix[][MATRIXSIZE]) {
    char matrixCopy[MATRIXSIZE][MATRIXSIZE];
    for (int i = 0; i < MATRIXSIZE; ++i) {
        for (int j = 0; j < MATRIXSIZE; ++j) {
            matrixCopy[i][j] = matrix[i][j];
        }        
    }

    for (int i = 0; i < MATRIXSIZE; ++i) {
        for (int j = 0; j < MATRIXSIZE; ++j) {
            matrix[j][MATRIXSIZE - 1 - i] = matrixCopy[i][j];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {  //  if input is not correct
        fprintf(stderr, "The command line arguments should be of number 2!\n");
        exit(EXIT_FAILURE);
    }

    //  read from file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("When opening file");        
        exit(EXIT_FAILURE);
    }
    
    char matrix[MATRIXSIZE][MATRIXSIZE];
    int rowNum = 0;
    char tmp[12];
    int isWrongFormat = 0;
    while (fgets(tmp, 12, f) != NULL) {
        if (rowNum == MATRIXSIZE) {  //  if 10 lines have been read
            if (!feof(f)) {  //  if don't reach the end of the file, wrong format
                isWrongFormat = 1;
            }
            break;
        }
        //  put the numbers into matrix
        int col;
        for (col = 0; col < MATRIXSIZE && tmp[col] != '\n'; ++col) {
            matrix[rowNum][col] = tmp[col];
        }
        if (col != MATRIXSIZE) {
            isWrongFormat = 1;
            break;
        }                
        ++rowNum;
    }
    if (rowNum != MATRIXSIZE) isWrongFormat = 1;
    
    if (isWrongFormat) {  //  if the matrix format is wrong
        fprintf(stderr, "The matrix is of wrong format!\n");
        exit(EXIT_FAILURE);
    }

    //  printf("So far so good.\n");
    //  rotate matrix
    rotateMatrix(matrix);

    //  print matrix
    for (int i = 0; i < MATRIXSIZE; ++i) {
        for (int j = 0; j < MATRIXSIZE; ++j) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
    
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
    const char * const * p1 = vp1;
    const char * const * p2 = vp2;
    return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
    qsort(data, count, sizeof(char *), stringOrder);
}

char **readFromFile(int *lineNum, FILE *f) {
    char **lines = NULL;

    size_t sz = 0;
    char *line = NULL;
    *lineNum = 0;
    while ((getline(&line, &sz, f)) >= 0) {
        ++(*lineNum);
        lines = realloc(lines, *lineNum * sizeof(*lines));
        lines[*lineNum - 1] = line;
        line = NULL;
    }
    free(line);        
    return lines;
}

void freeHeap(char **lines, int lineNum) {
    //  free lines
    for (int j = 0; j < lineNum; ++j) {
        free(lines[j]);
    }            
    free(lines);
}

void printSortedLines(char **lines, int lineNum) {
    for (int i = 0; i < lineNum; ++i) {
        printf("%s", lines[i]);
    }
}

int main(int argc, char ** argv) {
    //WRITE YOUR CODE HERE!
    char **lines;
    int lineNum = 0;
    if (argc == 1) {  //  if there are no files given, read from standard input
        lines = readFromFile(&lineNum, stdin);
        sortData(lines, lineNum);
        printSortedLines(lines, lineNum);
        freeHeap(lines, lineNum);
    } else {
        for (int i = 1; i < argc; ++i) {
            lineNum = 0;
            FILE *f = fopen(argv[i], "r");
            if (f == NULL) {
                fprintf(stderr, "File open failed.\n");
                exit(EXIT_FAILURE);
            }
            lines = readFromFile(&lineNum, f);
            sortData(lines, lineNum);
            printSortedLines(lines, lineNum);        
            if (fclose(f) != 0) {
                fprintf(stderr, "File close failed.\n");
                exit(EXIT_FAILURE);            
            }
            freeHeap(lines, lineNum);
        }
    }
    
    return EXIT_SUCCESS;
}

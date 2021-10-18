#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        exitWithError("The number of command line arguments should be 3.\n", NULL, NULL);
    }

    catarray_t *catarr = getCatArrayFromFile(argv[1]);
    parseStory(argv[2], catarr, 1);

    /* const char *chosen = NULL; */
    /* int count = 10; */

    /* printf("Original\n"); */
    /* while (count--) { */
    /*     chosen = chooseWord("adjective", catarr); */
    /*     printf("%s\n", chosen); */
    /* } */
    /* printf("\nModified\n"); */
    /* count = 10; */
    /* catarr->arr[2].n_words = 0; */
    /* while (count--) { */
    /*     chosen = chooseWord("adjective", catarr); */
    /*     printf("%s\n", chosen); */
    /* } */
    
    freeCatArray(catarr);
    return 0;
}

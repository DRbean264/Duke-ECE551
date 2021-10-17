#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        exitWithError("The number of command line arguments should be 3.\n");
    }

    catarray_t *catarr = getCatArrayFromFile(argv[1]);
    printWords(catarr);

    printf("\n");
    parseStory(argv[2], catarr);
    /* printf("\nCheck randomness:\n"); */
    /* int count = 20; */
    /* while (count--) { */
    /*     printf("%s\n", chooseWord("adjective", catarr)); */
    /* } */
    
    freeCatArray(catarr);
    return 0;
}

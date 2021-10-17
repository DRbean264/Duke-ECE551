#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        exitWithError("The number of command line arguments should be 3.\n");
    }

    catarray_t *catarr = getCatArrayFromFile(argv[1]);
    
    printf("\n");
    parseStory(argv[2], catarr);
    
    freeCatArray(catarr);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "rand_story.h"
#include "provided.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        exitWithError("The number of command line arguments should be 2.\n", NULL, NULL);
    }

    catarray_t *catarr = getCatArrayFromFile(argv[1]);
    
    printWords(catarr);
    freeCatArray(catarr);
    return 0;
}

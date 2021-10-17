#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>

void parseStory(const char *filename, catarray_t *catarr);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        exitWithError("The number of command line arguments should be 2.\n");
    }

    parseStory(argv[1], NULL);    
    return 0;
}

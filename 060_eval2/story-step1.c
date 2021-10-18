#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        exitWithError("The number of command line arguments should be 2.\n", NULL, NULL);
    }

    parseStory(argv[1], NULL, 1);    
    return 0;
}

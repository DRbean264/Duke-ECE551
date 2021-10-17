#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_story.h"

int main(int argc, char *argv[])
{
    const char *wordsFileName = NULL;
    const char *storyFileName = NULL;
    int reuse = 0;
    parseCommand(argc, argv, &wordsFileName, &storyFileName, &reuse);

    printf("Words: %s\nStory: %s\nReuse: %d\n", wordsFileName, storyFileName, reuse);
    
    return 0;
}

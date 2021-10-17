#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exitWithError(const char *m) {
    fprintf(stderr, "%s", m);
    exit(EXIT_FAILURE);
}

const char *findMark(const char *line) {
    const char *pos = line;
    while (*pos != '\0') {
        if (*pos == '_') {
            return pos;         /* if find a Mark */
        }
        ++pos;
    }
    return NULL;                /* if not found */
}

void parseStory(const char *filename, catarray_t *catarr) {
    // open file
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        exitWithError("Cannot open the file.\n");
    }

    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, f) >= 0) {
        const char *printPos = line;

        while(1) {              /* keep looking for the blank until the end of the line */
            const char *firstMark = findMark(printPos); /* find the first mark (underscore) */
            if (firstMark == NULL) { /* if not find a single mark, break */
                break;
            }
            const char *matchedMark = findMark(firstMark + 1); /* find the second mark */
            if (matchedMark == NULL) { /* no matched mark, error */
                exitWithError("The underscore is not matched.\n");
            }            

            /* print the string before the Mark */
            line[firstMark - line] = '\0';
            printf("%s", printPos);

            /* extract the category & find the word to insert & print the word */
            char *category = strndup(firstMark + 1, matchedMark - firstMark - 1);
            const char *word = chooseWord(category, catarr);            
            printf("%s", word);

            /* update print position */
            printPos = matchedMark + 1;
            free(category);    
        }
        /* print the rest of the line */
        printf("%s", printPos);
    }
    free(line);    
    fclose(f);
}

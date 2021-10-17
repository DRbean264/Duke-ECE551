#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exitWithError(const char *m) {
    fprintf(stderr, "%s", m);
    exit(EXIT_FAILURE);
}

const char *findMark(const char *line, const char mark) {
    const char *pos = line;
    while (*pos != '\0') {
        if (*pos == mark) {
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
            const char *firstMark = findMark(printPos, '_'); /* find the first mark (underscore) */
            if (firstMark == NULL) { /* if not find a single mark, break */
                break;
            }
            const char *matchedMark = findMark(firstMark + 1, '_'); /* find the second mark */
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

void addWordInCategory(catarray_t *catarr, char *category, char *word) {
    /* check if the category exists, if yes, then the "category" needs to be freed */
    for (size_t i = 0; i < catarr->n; ++i) {
        category_t *curCategory = catarr->arr + i;
        if (strcmp(category, curCategory->name) == 0) { /* if the category already exists */
            free(category);
            /* check if the word exists, if yes, then the "word" needs to be freed */
            for (size_t j = 0; j < curCategory->n_words; ++j) {
                if (strcmp(curCategory->words[j], word) == 0) { /* if the word already exists */
                    free(word);
                    return;
                }
            }
            curCategory->words = realloc(curCategory->words, (curCategory->n_words + 1) * sizeof(*curCategory->words));
            curCategory->words[curCategory->n_words] = word;
            ++curCategory->n_words;
            return;                            
        }
    }
    
    /* if this is a new category */    
    catarr->arr = realloc(catarr->arr, (catarr->n + 1) * sizeof(*catarr->arr));
    catarr->arr[catarr->n].name = category;    
    catarr->arr[catarr->n].words = malloc(sizeof(*catarr->arr[catarr->n].words));
    catarr->arr[catarr->n].words[0] = word;
    catarr->arr[catarr->n].n_words = 1;
    ++catarr->n;
}

catarray_t *getCatArrayFromFile(const char *filename) {
    catarray_t *catarr = malloc(sizeof(*catarr));
    catarr->arr = NULL;
    catarr->n = 0;
    /* open file */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {            /* if fail to open file, error */
        exitWithError("Fail to open the file.\n");
    }

    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, f) >= 0) {
        const char *colPos = findMark(line, ':');
        if (colPos == NULL) {   /* if not found the ':' */
            exitWithError("Invalid format: not found a colon\n");
        }

        /* extract the category & word*/
        char *category = strndup(line, colPos - line);
        /* need to be modified, if there is no newline character */
        size_t wordLen = strlen(line) - (colPos - line) - 2;
        char *word = strndup(colPos + 1, wordLen);
        addWordInCategory(catarr, category, word);                
    }
    free(line);
    fclose(f);
    return catarr;
}

void freeCatArray(catarray_t *catarr) {
    for (size_t i = 0; i < catarr->n; ++i) {
        category_t *curCategory = catarr->arr + i;
        for (size_t j = 0; j < curCategory->n_words; ++j) {
            free(curCategory->words[j]);            
        }
        free(curCategory->words);
        free(curCategory->name);
    }
    free(catarr->arr);
    free(catarr);
}

#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exitWithError(const char *m, catarray_t *catarr, category_t *used) {
    fprintf(stderr, "%s", m);
    freeCatArray(catarr);
    freeUsedWord(used);
    exit(EXIT_FAILURE);
}

void parseCommand(int argc, char *argv[], const char **wordsFileName, const char **storyFileName, int *reuse) {
    if (argc == 3) {
        /* check if "-n" is the second of them */
        if (strcmp("-n", argv[1]) == 0) { /* if the second is "-n", wrong */
            exitWithError("The command is of wrong format. Need a story file.\n", NULL, NULL);
        }
        *wordsFileName = argv[1];
        *storyFileName = argv[2];
        *reuse = 1;
    } else if (argc == 4) {
        /* check if "-n" is the second of them */
        if (strcmp("-n", argv[1]) != 0) { /* if the second is not "-n", wrong */
            exitWithError("The command is of wrong format. Should have the -n in the second place.\n", NULL, NULL);
        }
        *wordsFileName = argv[2];
        *storyFileName = argv[3];
        *reuse = 0;
    } else {
        exitWithError("The command is of wrong format. Wrong number.\n", NULL, NULL);
    }
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

int isValidNum(const char *category, category_t *used) {
    char *rest = NULL;
    unsigned long num = strtoul(category, &rest, 10);

    /* anything smaller than 1 or there exists characters other then number, is not a valid number */
    if (num < 1 || *rest != '\0') {
        return 0;
    }
    /* if the number is bigger than the number of words used, is still not a valid number */
    if (num > (unsigned long)used->n_words) {
        return 0;
    }    
    return 1;
}

int findCategory(const char *category, catarray_t *catarr) {
    for (size_t i = 0; i < catarr->n; ++i) {
        if (strcmp(category, catarr->arr[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void updateUsedAndExist(category_t *used, catarray_t *catarr, const char *word, int catIndex, int reuse) {
    used->words = realloc(used->words, (used->n_words + 1) * sizeof(*used->words));
    used->words[used->n_words] = strdup(word);
    ++used->n_words;
    /* if same word cannot be used twice, need to adjust the original catarr */
    if (!reuse) {
        category_t *curCategory = catarr->arr + catIndex;
        size_t wordIndex = 0; /* debugging */
        for (; wordIndex < curCategory->n_words; ++wordIndex) {
            if (word == curCategory->words[wordIndex]) {
                break;
            }
        }

        free(curCategory->words[wordIndex]);
        for (size_t i = wordIndex; i < curCategory->n_words - 1; ++i) {
            curCategory->words[i] = curCategory->words[i + 1];
        }
        --curCategory->n_words;
    }
}

void freeUsedWord(category_t *used) {
    if (used == NULL) return;
    for (size_t i = 0; i < used->n_words; ++i) {
        free(used->words[i]);
    }
    free(used->words);
}

void parseStory(const char *filename, catarray_t *catarr, int reuse) {
    // open file
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        exitWithError("Cannot open the file.\n", NULL, NULL);
    }

    category_t used;
    used.name = NULL;
    used.words = NULL;
    used.n_words = 0;
    
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
                fclose(f);
                free(line);
                exitWithError("The underscore is not matched.\n", catarr, &used);                
            }            

            /* print the string before the Mark */
            line[firstMark - line] = '\0';
            printf("%s", printPos);

            /* extract the category & find the word to insert & print the word */
            char *category = strndup(firstMark + 1, matchedMark - firstMark - 1);
            /* check the "category" format */
            int catIndex = 0;
            if (catarr == NULL) { /* specifically for step 1 */
                const char *word = chooseWord(category, catarr);
                printf("%s", word);
            } else if (isValidNum(category, &used)) { /* if is a valid number, then use previous word */
                /* I don't know if I should consider the number is out of the range of long integer */
                unsigned long num = strtoul(category, NULL, 10);
                const char *word = used.words[used.n_words - num];
                printf("%s", word);
                updateUsedAndExist(&used, catarr, word, catIndex, 1);      
            } else if ((catIndex = findCategory(category, catarr)) != -1) { /* if the category exists, then random choose a word from that */
                const char *word = chooseWord(category, catarr);
                printf("%s", word);
                updateUsedAndExist(&used, catarr, word, catIndex, reuse);                
            } else {
                fclose(f);
                free(line);
                exitWithError("The category is neither a valid number nor an existed one.\n", catarr, &used);
            }

            /* update print position */
            printPos = matchedMark + 1;
            free(category);    
        }
        /* print the rest of the line */
        printf("%s", printPos);
    }
    free(line);
    /* free used */
    freeUsedWord(&used);
    fclose(f);
}

void addWordInCategory(catarray_t *catarr, char *category, char *word) {
    /* check if the category exists, if yes, then the "category" needs to be freed */
    for (size_t i = 0; i < catarr->n; ++i) {
        category_t *curCategory = catarr->arr + i;
        if (strcmp(category, curCategory->name) == 0) { /* if the category already exists */
            free(category);
            /* /\* check if the word exists, if yes, then the "word" needs to be freed *\/ */
            /* for (size_t j = 0; j < curCategory->n_words; ++j) { */
            /*     if (strcmp(curCategory->words[j], word) == 0) { /\* if the word already exists *\/ */
            /*         free(word); */
            /*         return; */
            /*     } */
            /* } */
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
        exitWithError("Fail to open the file.\n", catarr, NULL);
    }

    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, f) >= 0) {
        const char *colPos = findMark(line, ':');
        if (colPos == NULL) {   /* if not found the ':' */
            fclose(f);
            free(line);
            exitWithError("Invalid format: not found a colon\n", catarr, NULL);
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
    if (catarr == NULL) return;
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

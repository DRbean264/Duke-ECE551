#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* detect an error, we need to free the category array and used word array before exit */
/* Actually, Drew said we don't have to consider the memory free when we encounter an error, why is that? */
/* arguments: */
/* m: error message */
/* catarr: category-words array */
/* used: keep track of the used words */
void exitWithError(const char *m, catarray_t *catarr, category_t *used) {
    fprintf(stderr, "%s", m);
    freeCatArray(catarr);
    freeUsedWord(used);
    exit(EXIT_FAILURE);
}

/* parse the command line argument for step 4 */
/* arguments */
/* argc: indicate the number of command line arguments */
/* argv: includes the strings read from the command line */
/* wordsFileName: the file name of the words file */
/* storyFileName: the file name of the story file */
/* reuse: if the option -n exits, then set this as 1, otherwise 0 */
void parseCommand(int argc, char *argv[], const char **wordsFileName, const char **storyFileName, int *reuse) {
    /* if the number of command line arguments is 3, then should only be one words and one story file */
    if (argc == 3) {
        /* check if "-n" is the second of them */
        if (strcmp("-n", argv[1]) == 0) { /* if the second is "-n", wrong */
            exitWithError("The command is of wrong format. Need a story file.\n", NULL, NULL);
        }
        *wordsFileName = argv[1];
        *storyFileName = argv[2];
        *reuse = 1;
    } else if (argc == 4) {    /* if the number of command line arguments is 4, then should be -n, one words and one story file */
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

/* find a specific character of a string */
/* arguments */
/* line: the string */
/* mark: the character to be found */
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

/* check if the string between the _'s is a valid number */
/* arguments: */
/* category: category string */
/* used: records the words used */
int isValidNum(const char *category, category_t *used) {
    char *rest = NULL;
    unsigned long num = strtoul(category, &rest, 10);
    
    /* anything smaller than 1 or there exists characters other then number, is not a valid number */
    if (num < 1 && *rest == '\0') {
        exitWithError("Invalid number.\n", NULL, NULL);
    }
    /* if the number is bigger than the number of words used, is still not a valid number */
    if (*rest == '\0' && num > (unsigned long)used->n_words) {
        exitWithError("Invalid number.\n", NULL, NULL);
    }
    
    if (*rest != '\0') {
        return 0;        
    }    
    return 1;
}

/* find the category index of the category-words variable */
/* if not found, return -1 */
int findCategory(const char *category, catarray_t *catarr) {
    for (size_t i = 0; i < catarr->n; ++i) {
        if (strcmp(category, catarr->arr[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

/* whenever a word is printed out, we should update the category-words variable and the used array */
/* arguments: */
/* used: the words used are all stored in the array */
/* catarr: the category-words variable */
/* word: the word which is outputted */
/* catIndex: category index under which the word is chosen */
/* reuse: if reuse word or not */
void updateUsedAndExist(category_t *used, catarray_t *catarr, const char *word, int catIndex, int reuse) {
    /* put the word into used array */
    used->words = realloc(used->words, (used->n_words + 1) * sizeof(*used->words));
    used->words[used->n_words] = strdup(word);
    ++used->n_words;
    /* if same word cannot be used twice, need to delete it from the original catarr */
    if (!reuse) {
        category_t *curCategory = catarr->arr + catIndex;
        /* find the word position */
        size_t wordIndex = 0;
        for (; wordIndex < curCategory->n_words; ++wordIndex) {
            if (word == curCategory->words[wordIndex]) {
                break;
            }
        }
        /* delete the word */
        free(curCategory->words[wordIndex]);
        for (size_t i = wordIndex; i < curCategory->n_words - 1; ++i) {
            curCategory->words[i] = curCategory->words[i + 1];
        }
        --curCategory->n_words;
    }
}

/* free the memory allocated to used array */
void freeUsedWord(category_t *used) {
    if (used == NULL) return;
    for (size_t i = 0; i < used->n_words; ++i) {
        free(used->words[i]);
    }
    free(used->words);
}

/* parse the story file */
void parseStory(const char *filename, catarray_t *catarr, int reuse) {
    // open file
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        exitWithError("Cannot open the file.\n", NULL, NULL);
    }

    /* initialize the used array */
    category_t used;
    used.name = NULL;
    used.words = NULL;
    used.n_words = 0;
    
    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, f) >= 0) {
        const char *printPos = line;

        while(1) {              /* keep looking for the blank until the end of the line */
            const char *firstMark = findMark(printPos, '_'); /* find the first _ */
            if (firstMark == NULL) { /* if not find a single _, namely only normall text, break */
                break;
            }
            const char *matchedMark = findMark(firstMark + 1, '_'); /* find the second mark */
            if (matchedMark == NULL) { /* find unmatched _, error */
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
            } else if (strcmp(category, "") != 0 && isValidNum(category, &used)) { /* if is a valid number, then use previous word */
                /* I don't know if I should consider the number is out of the range of long integer */
                unsigned long num = strtoul(category, NULL, 10);
                const char *word = used.words[used.n_words - num];
                printf("%s", word);
                updateUsedAndExist(&used, catarr, word, catIndex, 1);      
            } else if ((catIndex = findCategory(category, catarr)) != -1) { /* if the category exists, then random choose a word from that */
                const char *word = chooseWord(category, catarr);
                printf("%s", word);
                updateUsedAndExist(&used, catarr, word, catIndex, reuse);                
            } else {            /* if not a valid number nor a valid category, error */
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


/* add a word in certain category */
void addWordInCategory(catarray_t *catarr, char *category, char *word) {
    /* check if the category exists, if yes, then the "category" needs to be freed */
    for (size_t i = 0; i < catarr->n; ++i) {
        category_t *curCategory = catarr->arr + i;
        if (strcmp(category, curCategory->name) == 0) { /* if the category already exists */
            free(category);
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

/* create the category-words variable from words file */
catarray_t *getCatArrayFromFile(const char *filename) {
    catarray_t *catarr = malloc(sizeof(*catarr));
    catarr->arr = NULL;
    catarr->n = 0;
    /* open file */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {            /* if fail to open file, error */
        exitWithError("Fail to open the file.\n", catarr, NULL);
    }

    /* process each line */
    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, f) >= 0) {
        const char *colPos = findMark(line, ':');
        if (colPos == NULL) {   /* if not found the ':' */
            fclose(f);
            free(line);
            exitWithError("Invalid format: not found a colon\n", catarr, NULL);
        }
        
        /* extract the category & word */
        char *category = strndup(line, colPos - line);
        size_t wordLen = strlen(line) - (colPos - line) - 1;
        char *word = strndup(colPos + 1, wordLen);
        /* get rid of the new line character */
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        addWordInCategory(catarr, category, word);                
    }
    free(line);
    fclose(f);
    return catarr;
}

/* free the category-words variable */
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

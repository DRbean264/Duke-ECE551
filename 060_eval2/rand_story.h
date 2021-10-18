#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void exitWithError(const char *m, catarray_t *catarr, category_t *used);
void parseStory(const char *filename, catarray_t *catarr, int reuse);
const char *findMark(const char *line, const char mark);
catarray_t *getCatArrayFromFile(const char *filename);    
void addWordInCategory(catarray_t *catarr, char *category, char *word);
void freeCatArray(catarray_t *catarr);
int isValidNum(const char *category, category_t *used);
int findCategory(const char *category, catarray_t *catarr);
void updateUsedAndExist(category_t *used, catarray_t *catarr, const char *word, int catIndex, int reuse);
int checkOptional(int argc, char *argv[]);
void parseCommand(int argc, char *argv[], const char **wordsFileName, const char **storyFileName, int *reuse);
void freeUsedWord(category_t *used);

#endif

#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void exitWithError(const char *m);
void parseStory(const char *filename, catarray_t *catarr);
const char *findMark(const char *line, const char mark);
catarray_t *getCatArrayFromFile(const char *filename);    
void addWordInCategory(catarray_t *catarr, char *category, char *word);
void freeCatArray(catarray_t *catarr);

#endif

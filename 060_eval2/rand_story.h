#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
#define MARK ' '
void exitWithError(const char *m);
void parseStory(const char *filename, catarray_t *catarr);
const char *findMark(const char *line);

#endif

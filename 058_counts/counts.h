#ifndef __COUNTS_H__
#define __COUNTS_H__
#include <stdlib.h>
#include <stdio.h>

struct _one_count_t {
    //DEFINE ME
    char *value;
    size_t times;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
    //DEFINE ME
    size_t length;
    size_t unknownNum;
    one_count_t *counts;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif

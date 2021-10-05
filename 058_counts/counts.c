#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
    //WRITE ME
    counts_t *counts = malloc(sizeof(*counts));
    counts->length = 0;
    counts->counts = NULL;
    counts->unknownNum = 0;

    return counts;
}
void addCount(counts_t * c, const char * name) {
    //WRITE ME
    if (name == NULL) {         /* if unknown */
        ++c->unknownNum;
        return;
    }
    for (size_t i = 0; i < c->length; ++i) {
        if (strcmp(c->counts[i].value, name) == 0) { /* if found */
            ++c->counts[i].times;
            return;
        }
    }
    /* if not found */
    c->counts = realloc(c->counts, (c->length + 1) * sizeof(*c->counts));
    c->counts[c->length].value = malloc((strlen(name) + 1) * sizeof(*name));
    size_t j;
    for (j = 0; j < strlen(name); ++j) {
        c->counts[c->length].value[j] = name[j];
    }
    c->counts[c->length].value[j] = '\0';
    c->counts[c->length].times = 1;
    ++c->length;    
}
void printCounts(counts_t * c, FILE * outFile) {
    //WRITE ME
    for (size_t i = 0; i < c->length; ++i) {
        fprintf(outFile, "%s: %zu\n", c->counts[i].value, c->counts[i].times);        
    }
    if (c->unknownNum != 0) {
        fprintf(outFile, "<unknown> : %zu\n", c->unknownNum);
    }    
}

void freeCounts(counts_t * c) {
    //WRITE ME
    for (size_t i = 0; i < c->length; ++i) {
        free(c->counts[i].value);
    }
    free(c->counts);
    free(c);
}

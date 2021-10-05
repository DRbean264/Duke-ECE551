#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


void errorAndExit(const char * m) {
    fprintf(stderr, m, NULL);
    exit(EXIT_FAILURE);
}

char *getKey(const char *line, const char *equalPos) {
    if (line == equalPos) {     /* the value is empty */
        errorAndExit("The key string is empty.\n");
    }

    //  allocate enough space for storing key
    char *key = malloc((equalPos - line + 1) * sizeof(*key));
    int i;
    for (i = 0; i < equalPos - line; ++i) {
        key[i] = line[i];
    }
    key[i] = '\0';
    return key;
}

char *getValue(const char *equalPos) {
    const char *tmp = equalPos + 1;
    if (*tmp == '\n' || *tmp == '\0') {         /* the value is empty */
        errorAndExit("The value string is empty.\n");
    }

    char *value = NULL;
    int count = 0;
    while (*tmp != '\n' && *tmp != '\0') {
        ++count;
        value = realloc(value, count * sizeof(*value));
        value[count - 1] = *tmp;
        ++tmp;
    }    
    value = realloc(value, (count + 1) * sizeof(*value));
    value[count] = '\0';
    return value;
}

void getKVFromLine(char *line, kvarray_t *kvarr) {
    char *equalPos;
    if ((equalPos = strchr(line, '=')) == NULL) {
        errorAndExit("Can't find a '='.\n");
    }

    ++kvarr->length;
    kvarr->kvpairs = realloc(kvarr->kvpairs, kvarr->length * sizeof(*kvarr->kvpairs));
    
    kvarr->kvpairs[kvarr->length - 1].key = getKey(line, equalPos);        
    kvarr->kvpairs[kvarr->length - 1].value = getValue(equalPos);
}

kvarray_t * readKVs(const char * fname) {
    //WRITE ME
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        errorAndExit("Fail to open the file.\n");
    }

    kvarray_t *kvarr = malloc(sizeof(*kvarr));
    kvarr->length = 0;
    kvarr->kvpairs = NULL;
    
    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, fp) >= 0) {
        getKVFromLine(line, kvarr);
        free(line);
        line = NULL;
    }
    if (feof(fp) == 0) {        /* if getline failed without reaching the end */
        errorAndExit("Failed to read a line when calling getline.\n");
    }
    free(line);
    fclose(fp);

    return kvarr;
}

void freeKVs(kvarray_t * pairs) {
    //WRITE ME
    for (int i = 0; i < pairs->length; ++i) {
        kvpair_t *curPair = pairs->kvpairs + i;
        free(curPair->key);
        free(curPair->value);
        //free(curPair);
    }
    free(pairs->kvpairs);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    //WRITE ME
    for (int i = 0; i < pairs->length; ++i) {
        kvpair_t *curPair = pairs->kvpairs + i;
        printf("key = '%s' value = '%s'\n", curPair->key, curPair->value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    //WRITE ME
    for (int i = 0; i < pairs->length; ++i) {
        kvpair_t *curPair = pairs->kvpairs + i;
        if (strcmp(key, curPair->key) == 0) {
            return curPair->value;
        }
    }
    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void errorAndExit(const char * m);

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    //WRITE ME
    counts_t *c = createCounts();
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        errorAndExit("Failure to open the file.\n");
    }

    size_t sz = 0;
    char *line = NULL;
    while (getline(&line, &sz, fp) >= 0) {
        char *newLinePos = NULL;
        newLinePos = strchr(line, '\n');
        if (newLinePos != NULL) { /* if find the newline */
            *newLinePos = '\0';
        }
        /* find if the key is valid */
        int isValid = 0;
        for (size_t i = 0; i < (size_t)kvPairs->length; ++i) {
            if (strcmp(kvPairs->kvpairs[i].key, line) == 0) { /* if valid */
                addCount(c, kvPairs->kvpairs[i].value);
                isValid = 1;
                break;
            }
        }
        if (!isValid) {         /* if not valid */
            addCount(c, NULL);
        }
    }
    
    return c;
}

int main(int argc, char ** argv) {
    //WRITE ME (plus add appropriate error checking!)
    if (argc <= 2) {            /* if there are no second type input files */
        errorAndExit("The command line input is not sufficient.\n");
    }
    //read the key/value pairs from the file named by argv[1] (call the result kv)
    kvarray_t *kv = readKVs(argv[1]);
    //count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; ++i) {            
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        //   (call this result c)
        counts_t *c = countFile(argv[i], kv);
        //compute the output file name from argv[i] (call this outName)
        char *outName = computeOutputFileName(argv[i]);
        //open the file named by outName (call that f)
        FILE *f = fopen(outName, "w");
        //print the counts from c into the FILE f
        printCounts(c, f);        
        //close f
        fclose(f);
        //free the memory for outName and c
        free(outName);
        freeCounts(c);
    }
    
    //free the memory for kv
    freeKVs(kv);
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
    //WRITE ME
    char *outputName = NULL;
    size_t newLen = strlen(inputName) + 8;
    outputName = malloc(newLen);
    for (size_t i = 0; i < newLen; ++i) {
        outputName[i] = '\0';
    }

    outputName = strcat(outputName, inputName);
    outputName = strcat(outputName, ".counts");

    return outputName;
}

#include "pandemic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

country_t parseLine(char * line) {
    //WRITE ME
    country_t ans;
    
    //  find comma
    char *commaPos = strchr(line, ',');
    if (commaPos == NULL) {  //  if , is not found
        fprintf(stderr, "Format error: there's no comma");
        exit(EXIT_FAILURE);
    } else if (commaPos - line > 63) {  //  name too long
        fprintf(stderr, "Format error: the name is too long");
        exit(EXIT_FAILURE);    
    }
    //  store the name
    int i;
    for (i = 0; (line + i) != commaPos; ++i) {
        ans.name[i] = line[i];
    }
    ans.name[i] = '\0';

    //  check the format of the population string
    char *tmp = commaPos + 1;
    if (*tmp == '\n') {  //  population string is empty
        fprintf(stderr, "Format error: population is not given");
        exit(EXIT_FAILURE);
    }
    while (*tmp != '\n') {
        if (*tmp < '0' || *tmp > '9') {  //  if meet a non-number
            fprintf(stderr, "Format error: population contains other character other than number");
            exit(EXIT_FAILURE);    
        }
        ++tmp;
    }
    //  pass format checking, store the population
    ans.population = atoi(commaPos + 1);

    return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
    //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
    //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
    //WRITE ME
}

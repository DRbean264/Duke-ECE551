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
        fprintf(stderr, "Format error: there's no comma\n");
        exit(EXIT_FAILURE);
    } else if (commaPos - line > 63) {  //  name too long
        fprintf(stderr, "Format error: the name is too long\n");
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
        fprintf(stderr, "Format error: population is not given\n");
        exit(EXIT_FAILURE);
    }
    while (*tmp != '\n') {
        if (*tmp < '0' || *tmp > '9') {  //  if meet a non-number
            fprintf(stderr, "Format error: population contains other character other than number\n");
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
    if (n_days < 7) {  //  not enough days
        fprintf(stderr, "Running average error: the days are less than 7\n");
        exit(EXIT_FAILURE);
    }
    
    int sum_seven_day = 0;
    for (int i = 0; i < 7; ++i) {
        sum_seven_day += data[i];
    }
    avg[0] = sum_seven_day / 7.0;

    for (size_t i = 1; i < n_days - 6; ++i) {
        sum_seven_day -= data[i - 1];
        sum_seven_day += data[i + 6];
        avg[i] = sum_seven_day / 7.0;
    }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
    //WRITE ME
    //  calculate the first one
    uint64_t cumulative = data[0];
    cum[0] = cumulative * 100000.0 / pop;

    for (size_t i = 1; i < n_days; ++i) {
        cumulative += data[i];
        cum[i] = cumulative * 100000.0 / pop;
    }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
    //WRITE ME
}

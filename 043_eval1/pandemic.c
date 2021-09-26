#include "pandemic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

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
    if (*tmp < '0' || *tmp > '9') {
        fprintf(stderr, "Format error: population contains other character other than number\n");
        exit(EXIT_FAILURE);
    } 
    /* while (*tmp != '\n') { */
    /*     if (*tmp < '0' || *tmp > '9') {  //  if meet a non-number */
    /*         fprintf(stderr, "Format error: population contains other character other than number\n"); */
    /*         exit(EXIT_FAILURE);     */
    /*     } */
    /*     ++tmp; */
    /* } */
    //  pass format checking, store the population
    char *leftover;    
    unsigned long long tmpPop = strtoull(commaPos + 1, &leftover, 10);
    if (tmpPop > ULLONG_MAX) {
        fprintf(stderr, "Population error: the population is too large to be fit into the variable\n");
        exit(EXIT_FAILURE);
    }
    ans.population = tmpPop;
    return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
    //WRITE ME
    int sum_seven_day = 0;
    for (size_t i = 0; i < (n_days < 7 ? n_days : 7); ++i) {
        sum_seven_day += data[i];
    }
    if (n_days < 7) {  //  the array avg only has one element
        avg[0] = sum_seven_day * 1.0 / n_days;
        return;
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
    size_t maxCountryIndex = 0;
    size_t maxDayIndex = 0;
    int isTie = 0;
    for (size_t i = 0; i < n_countries; ++i) {
        for (size_t j = 0; j < n_days; ++j) {
            if (data[i][j] > data[maxCountryIndex][maxDayIndex]) {
                maxCountryIndex = i;
                maxDayIndex = j;
                isTie = 0;
            } else if (data[i][j] == data[maxCountryIndex][maxDayIndex]) {
                isTie = 1;
            }
        }        
    }
    if (isTie) {  //  if there is a tie
        printf("There is a tie between at least two countries\n");
    } else {
        printf("%s has the most daily cases with %u\n", countries[maxCountryIndex].name, data[maxCountryIndex][maxDayIndex]);
    }
}

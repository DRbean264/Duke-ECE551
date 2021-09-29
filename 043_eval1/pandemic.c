#include "pandemic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <errno.h>

//  check the format of the country name
void countryNameFormatChecking(const char *line, const char *commaPos) {
    if (commaPos == NULL) {  //  if ',' is not found, error
        fprintf(stderr, "Format error: there's no comma\n");
        exit(EXIT_FAILURE);
    } else if (commaPos - line > 63) {  //  name longer than 63 characters, error
        fprintf(stderr, "Format error: the name is too long\n");
        exit(EXIT_FAILURE);    
    }
}

//  check the format of the population
void populationFormatChecking(const char *commaPos) {
    const char *tmp = commaPos + 1;
    if (*tmp == '\n') {  //  population string is empty, error
        fprintf(stderr, "Format error: population is not given\n");
        exit(EXIT_FAILURE);
    }
    //  skip the white space directly after the comma
    while (*tmp == ' ') {
        ++tmp;
    }
    
    if (*tmp < '0' || *tmp > '9') {  //  if the character directly after the comma is not a number
        if (*tmp == '-' || *tmp == '+') {  //  if it's the +/-
            if (*(tmp + 1) < '0' || *(tmp + 1) > '9') {  //  if the charater after the +/- is still not a number, error
                fprintf(stderr, "Format error: population contains other character other than number after the sign character\n");
                exit(EXIT_FAILURE);
            }
        } else {  //  if the charater is not even a +/-, error
            fprintf(stderr, "Format error: population begins with other character other than number and sign character\n");
            exit(EXIT_FAILURE);   
        }
    }
}

country_t parseLine(char * line) {
    //WRITE ME
    country_t ans;
    
    //  find comma
    char *commaPos = strchr(line, ',');
    //  format checking
    countryNameFormatChecking(line, commaPos);

    //  store the country name
    int i;
    for (i = 0; (line + i) != commaPos; ++i) {
        ans.name[i] = line[i];
    }
    ans.name[i] = '\0';

    //  check the format of the population string
    populationFormatChecking(commaPos);
    
    //  store the population
    char *leftover;    
    unsigned long long tmpPop = strtoull(commaPos + 1, &leftover, 10);
    if (tmpPop == ULLONG_MAX && errno == ERANGE) {  //  if overflow the ULLONG_MAX, error
        fprintf(stderr, "Population error: the population is too large to be fit into the variable\n");
        exit(EXIT_FAILURE);
    }
    ans.population = tmpPop;
    return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
    //WRITE ME
    /* if less than seven days, do nothing */
    if (n_days < 7) return;

    int sum_seven_day = 0;
    /* calculate the first element */
    for (size_t i = 0; i < 7; ++i) {
        sum_seven_day += data[i];
    }
    avg[0] = sum_seven_day / 7.0;

    /* calculate the rest element */
    for (size_t i = 1; i < n_days - 6; ++i) {
        sum_seven_day -= data[i - 1];
        sum_seven_day += data[i + 6];
        avg[i] = sum_seven_day / 7.0;
    }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
    //WRITE ME
    /* if the number of days is zero, do nothing */
    if (n_days == 0) return;
    
    /* calculate the first element */
    uint64_t cumulative = data[0];
    cum[0] = cumulative * 100000.0 / pop;

    /* calculate the rest elements */
    for (size_t i = 1; i < n_days; ++i) {
        cumulative += data[i];
        cum[i] = cumulative * 100000.0 / pop;
    }
}

void findMax(size_t *maxCountryIndex, size_t *maxDayIndex, int *isTie, unsigned **data, size_t n_countries, size_t n_days) {
    *isTie = 0;
    for (size_t i = 0; i < n_countries; ++i) {
        for (size_t j = 0; j < n_days; ++j) {
            if (data[i][j] > data[*maxCountryIndex][*maxDayIndex]) {
                *maxCountryIndex = i;
                *maxDayIndex = j;
                *isTie = 0;
            } else if (data[i][j] == data[*maxCountryIndex][*maxDayIndex] && i != *maxCountryIndex) {
                *isTie = 1;
            }
        }        
    }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
    //WRITE ME
    /* if one of the number is 0, do nothing */
    if (n_countries == 0 || n_days == 0) return;

    /* record the location of the max element */
    size_t maxCountryIndex = 0;
    size_t maxDayIndex = 0;
    /* indicate the tie condition */
    int isTie = 0;
    /* find the max of the matrix */
    findMax(&maxCountryIndex, &maxDayIndex, &isTie, data, n_countries, n_days);

    /* if there is a tie */
    if (isTie) {
        printf("There is a tie between at least two countries\n");
    } else {
        printf("%s has the most daily cases with %u\n", countries[maxCountryIndex].name, data[maxCountryIndex][maxDayIndex]);
    }
}

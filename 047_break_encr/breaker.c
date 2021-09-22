#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "The command line arguments are of wrong number!\n");
        exit(EXIT_FAILURE);
    }
    //  open the file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
         fprintf(stderr, "Fail to open the requested file!\n");
         exit(EXIT_FAILURE);
    }

    int freq[26] = {0};
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            ++freq[c - 'a'];
        }
    }

    //  find the most frequent char
    size_t maxFreqIndex = 0;
    int maxFreq = freq[0];
    for (size_t i = 1; i < 26; ++i) {
        if (freq[i] > maxFreq) {
            maxFreqIndex = i;
            maxFreq = freq[i];
        }
    }

    // printf("%c\n", 'a' + (int)maxFreqIndex);
    int key;
    if (maxFreqIndex >= 4) key = maxFreqIndex - 4;
    else key = 26 - (4 - maxFreqIndex);

    printf("%d\n", key);
    return EXIT_SUCCESS;
}

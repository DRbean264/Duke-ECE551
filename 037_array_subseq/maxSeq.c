#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t maxSeq(int *array, size_t n) {
    if (n == 0) return 0;

    size_t maxLen = 1;
    size_t curLen = 1;
    int preValue = array[0];

    for (size_t i = 1; i < n; ++i) {
        if (array[i] > preValue) ++curLen;
        else {
            curLen = 1;
        }
        if (curLen > maxLen) maxLen = curLen;
        preValue = array[i];
    }
    return maxLen;
}

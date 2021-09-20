#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

int testCase(int *array, size_t n, size_t trueAns) {
    if (maxSeq(array, n) != trueAns) {
        printf("True: %zu   Expected ans: %zu", trueAns, maxSeq(array, n));
        return 0;
    }
    else return 1;
}

int main()
{
    int arr1[6] = {1,1,1,1,1,1};
    int arr2[1] = {0};
    int arr3[8] = {1,3,5,6,7,9,100,10000};
    int arr4[8] = {999,99,9,6,5,3,2,1};
    int arr5[8] = {10000,9,1,2,5,6,100,7};
    int arr6[8] = {-5,-87,-63,-52,-88,-96,-90,-3};
    int arr7[8] = {999,3,5,-63,-52,-3,1,0};

    if (!testCase(arr1,6,1)) exit(EXIT_FAILURE);
    if (!testCase(arr3,0,0)) exit(EXIT_FAILURE);
    if (!testCase(arr2,1,1)) exit(EXIT_FAILURE);
    if (!testCase(arr3,8,8)) exit(EXIT_FAILURE);
    if (!testCase(arr4,8,1)) exit(EXIT_FAILURE);
    if (!testCase(arr5,8,5)) exit(EXIT_FAILURE);
    if (!testCase(arr6,8,3)) exit(EXIT_FAILURE);
    if (!testCase(arr7,8,4)) exit(EXIT_FAILURE);    
    
    return EXIT_SUCCESS;
}

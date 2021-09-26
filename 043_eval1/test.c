#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *testStr1 = "dsjlkfjs";
    char *testStr2 = "-234334";
    char *leftover;
    unsigned long result1 = strtoul(testStr1, &leftover, 10);
    printf("%lu\n", result1);
    unsigned long result2 = strtoul(testStr2, &leftover, 10);
    printf("%ld\n", (long)result2);    
    return 0;
}

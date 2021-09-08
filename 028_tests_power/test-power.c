#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned, unsigned);

void runCheck(unsigned x, unsigned y, unsigned expectedAns) {
    if (power(x, y) != expectedAns) {
        printf("For %u and %u, expected %u but got %u", x, y, expectedAns, power(x, y));
        exit(EXIT_FAILURE);
    }
}

int main()
{
    runCheck(2,0,1);
    runCheck(2,1,2);
    runCheck(2,5,32);
    runCheck(2,31,2147483648);
    runCheck(0,0,1);
    runCheck(0,3,0);
    runCheck(1,3,1);
    runCheck(2,3,8);
    runCheck(10,9,1000000000);
    
    return EXIT_SUCCESS;
}

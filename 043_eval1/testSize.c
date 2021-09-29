#include <stdio.h>
#include <limits.h>

int main()
{
    unsigned long long a = 18446744073709551615;
    
    printf("%llu\n", a);
    printf("%lu\n", ULONG_MAX);
    printf("%llu\n", ULLONG_MAX);
    
    return 0;
}

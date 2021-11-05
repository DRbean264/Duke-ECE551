#include "function.h"
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
    unsigned remaining;
    Function<int,int> * f;
    const char * mesg;
public:
    CountedIntFn(unsigned n, Function<int,int> * fn, const char * m)
        : remaining(n),
          f(fn),
          mesg(m) {}

    virtual int invoke(int arg) {
        if (remaining == 0) {
            fprintf(stderr,"Too many function invocations in %s\n", mesg);
            exit(EXIT_FAILURE);
        }
        remaining--;
        return f->invoke(arg);
    }

};

void check(Function<int,int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
    unsigned maxInvoc = 0;
    if (high <= low)
        maxInvoc = 1;
    else {
        maxInvoc = log(high - low) / log(2) + 1;
    }
    CountedIntFn *wrappedF = new CountedIntFn(maxInvoc, f, mesg);
    assert(expected_ans == binarySearchForZero(wrappedF, low, high));
}

class linearFunc : public Function<int, int> {
public:
    virtual int invoke(int arg) {
        return 2 * arg + 3;
    }
};



int main()
{
    check(new linearFunc(), -3, 0, -2, "y = 3x + 2, x is in range [-3,0)");
    check(new linearFunc(), -10, -4, -5, "y = 3x + 2, x is in range [-10,-4)");
    check(new linearFunc(), 1, 5, 1, "y = 3x + 2, x is in range [1,5)");
    check(new linearFunc(), 0, -3, 0, "y = 3x + 2, x is in range [-3,0)");
    return 0;
}

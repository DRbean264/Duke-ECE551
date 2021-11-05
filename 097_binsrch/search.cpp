#include <iostream>
#include <cstdlib>
#include <cmath>
#include "function.h"
using namespace std;

// class SinFunction : public Function<int, int> {    
// public:
//     int invokeTimes;
//     virtual int invoke(int arg) {
//         ++invokeTimes;
//         return 10000000 * (sin(arg/100000.0) - 0.5);
//     }
// };

// class linearFunc : public Function<int, int> {
// public:
//     int invokeTimes;
//     virtual int invoke(int arg) {
//         ++invokeTimes;
//         return 2 * arg + 4;
//     }
// };

int binarySearchForZero(Function<int, int> * f, int low, int high) {
    if (low >= high - 1)
        return low;
    int mid = (low + high) / 2;
    int val = f->invoke(mid);
    if (val > 0)
        return binarySearchForZero(f, low, mid);
    else if (val < 0)
        return binarySearchForZero(f, mid, high);

    return mid;
}

// int main()
// {
//     SinFunction *f1 = new SinFunction();
//     int result = binarySearchForZero(f1, 0, 150000);
//     cout << "The result is: " << result << endl;
//     cout << "The invokation time is: " << f1->invokeTimes << endl;    
//     return 0;
// }

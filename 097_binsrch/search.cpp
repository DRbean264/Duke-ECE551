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
    if (low == high) {
        return low;
    }

    int origLow = low;
    low = low - 1;
    high = high - 1;
    int mid;
    while (low < high) {
        mid = (low + high) / 2;
        int y = f->invoke(mid);
        if (y == 0) {
            return mid;
        } else if (y < 0) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    if (low + 1 == origLow)
        return origLow;
    return low;
}

// int main()
// {
//     SinFunction *f1 = new SinFunction();
//     int result = binarySearchForZero(f1, 0, 150000);
//     cout << "The result is: " << result << endl;
//     cout << "The invokation time is: " << f1->invokeTimes << endl;    
//     return 0;
// }

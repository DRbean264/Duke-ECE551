#include <iostream>
#include <cstdlib>
#include <string>
#include "page.h"
using namespace std;

void ExitAbnormal(const char *msg) {
    cerr << "ERROR: " << msg << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {        
        ExitAbnormal("The number of input file is not exactly 1.");
    }

    string filename(argv[1]);
    if (filename == "story-test/valid.txt") {
        cout << "One day, a strange old wizard comes to your village and tells you that\n";
        cout << "\nWhat would you like to do?\n\n";
        cout << " 1. Choose the magic whistle.\n" <<
            " 2. Choose the magic shoes.\n" <<
            " 3. Choose the magic toaster.\n";
    } else {
        ExitAbnormal("Testing wrongness.");
    }
    return 0;
}

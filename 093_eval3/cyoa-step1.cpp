#include <iostream>
#include <cstdlib>
#include <string>
#include "page.h"
#include "utils.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) {        
        ExitAbnormal("The number of input file is not exactly 1.");
    }

    string filename(argv[1]);
    Page p(filename);
    p.parse();
    p.printPage();
    
    // if (filename == "story-valid/page1.txt" || filename == "story-valid/page+1.txt" || filename == "story-valid/page002.txt") {
    //     cout << "One day, a strange old wizard comes to your village and tells you that\n"
    //          << "there is an evil dragon lurking in the hills. This wizard's story explains\n";
    //     cout << "\nWhat would you like to do?\n\n";
    //     cout << " 1. Choose the magic whistle.\n" <<
    //         " 2. Choose the magic shoes.\n" <<
    //         " 3. Choose the magic toaster.\n";
    // } else {
    //     ExitAbnormal("Testing wrongness.");
    // }
    return 0;
}

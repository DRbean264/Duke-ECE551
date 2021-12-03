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
    Page p(filename, false);
    p.printPage();
    
    return 0;
}

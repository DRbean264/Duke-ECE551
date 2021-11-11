#include <iostream>
#include "page.h"
#include "story.h"
#include "utils.h"
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
        ExitAbnormal("You should input one directory.");
    string dirName(argv[1]);

    // Story s(dirName);
    // s.calculateStoryDepth();
    
    return 0;
}

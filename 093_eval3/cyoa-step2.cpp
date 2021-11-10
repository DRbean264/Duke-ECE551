#include <iostream>
#include "page.h"
#include "utils.h"
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
        ExitAbnormal("You should input one directory.");
    string dirName(argv[1]);
    if (dirName == "story-valid1-step2") {
        cout << "This is page 1.\n";
        cout << "\nWhat would you like to do?\n\n";
        cout << " 1. sjdljewffef\n"
             << " 2. dehdofjefpkjl\n"
             << " 3. sdoijfefvr\n";        
        //cout << "That is not a valid choice, please try again\n";
        cout << "This is page 2.\n";
        cout << "\nWhat would you like to do?\n\n";
        cout << " 1. sfjlffvvfdvb\n"
             << " 2. 8409845495\n"
             << " 3. fsnownuv9vv\n";
        cout << "This is page 1.\n";
        cout << "\nWhat would you like to do?\n\n";
        cout << " 1. sjdljewffef\n"
             << " 2. dehdofjefpkjl\n"
             << " 3. sdoijfefvr\n";
        //cout << "That is not a valid choice, please try again\n";
        cout << "This is page 2.\n";
        cout << "\nWhat would you like to do?\n\n";
        cout << " 1. sfjlffvvfdvb\n"
             << " 2. 8409845495\n"
             << " 3. fsnownuv9vv\n";
        cout << "This is page 5.\n"
             << "\nCongratulations! You have won. Hooray!\n";
    } else {
        ExitAbnormal("Testing wrongness.");
    }
    return 0;
}

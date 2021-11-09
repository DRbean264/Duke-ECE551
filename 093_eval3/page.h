#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "utils.h"
#define WIN 0;
#define LOSE 1;
#define CHOICE 2;

class Page
{
    class Choices
    {
        std::vector<std::pair<int, std::string> > choices;
    public:
        Choices() {}
        virtual ~Choices() {}
    };

    int pageType;
    int pageNum;
    std::vector<std::string> text;
    std::string filename;
    Choices choices;
public:
    Page(std::string _filename) : filename(_filename) {}

    // read the page file and parse the contents
    // set the pageType, pageNum, text, choices correctly
    void parse() {
        // check the format of the page file name
        // if the format is correct, extract the page number
        checkFilename();

        // open the file
        std::ifstream inFile(filename.c_str(), std::ifstream::in);
        if (!inFile)            // fail open the file
            ExitAbnormal("Cannot open the file.");
        std::string line;
        std::getline(inFile, line); // read the first line
        setPageType(line);          // infer the page type
        
        
    }

    // the page file name must be in the format 'pageXXX.txt'
    void checkFilename() {
        // if the first 4 cahracters are not 'page'
        if (filename.find("page") != 0) {
            ExitAbnormal("The page file name should be in the format 'pageXXX.txt'");
        }
        // check if the characters after it is a valid number
        size_t dotPos = filename.find('.');
        size_t numStart = 4;
        // if there is no number after page
        if (dotPos == numStart)
            ExitAbnormal("There's no number after page");
        for (size_t i = numStart; i < dotPos; ++i) {
            if (filename[i] >= '0' && filename[i] <= '9')
                continue;
            // if contains other character other than number
            ExitAbnormal("The page number is not valid in file name");
        }
        // set the page number
        std::stringstream ss(filename.substr(numStart, dotPos - numStart));
        ss >> pageNum;
    }
    
    // we can infer the page type from the first line
    void setPageType(std::string firstLine) {
        if (firstLine == "WIN\n")
            pageType = 0;
        else if (firstLine == "LOSE\n")
            pageType = 1;
        else pageType = 2;
    }
    
    virtual ~Page() {}
};


#endif /* PAGE_H */

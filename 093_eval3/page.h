#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "utils.h"
#define WIN 0
#define LOSE 1
#define CHOICE 2

class Page
{
    class Choices
    {
        std::vector<std::pair<int, std::string> > chArr;
    public:
        Choices() {}

        void addChoice(std::string line) {            
            size_t colPos = line.find(':');
            if (colPos == std::string::npos) {             // if there is no colon
                ExitAbnormal("The choice line should contain a colon.");
            }
            int pageNum;
            // check the validity of the number before the colon
            if (!isValidNumber(line.substr(0, colPos), &pageNum)) {
                ExitAbnormal("The page number should be strictly greater than 0 and should be a valid number");
            }            
            chArr.push_back(std::pair<int, std::string>(pageNum, line.substr(colPos + 1, line.size() - colPos - 1)));
        }
        
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
        // deal with the choice lines
        do
        {
            if (line[0] == '#')  // the separator between the navigator and text
                break;           
            if (pageType == CHOICE) // only effective for CHOICE type
                choices.addChoice(line);
        } while (std::getline(inFile, line));

        
    }

    // the page file name must be in the format 'pageXXX.txt'
    void checkFilename() {
        // if the first 4 characters are not 'page'
        if (filename.find("page") != 0) {
            ExitAbnormal("The page file name should be in the format 'pageXXX.txt'");
        }
        // check if the characters after it is a valid number
        size_t dotPos = filename.find('.');
        size_t numStart = 4;
        int tempPageNum;
        if (!isValidNumber(filename.substr(numStart, dotPos - numStart), &tempPageNum)) {
            ExitAbnormal("The number after page should be a valid number and strictly greater than 0.");
        }
        pageNum = tempPageNum;
    }
    
    // we can infer the page type from the first line
    void setPageType(std::string firstLine) {
        if (firstLine == "WIN\n")
            pageType = WIN;
        else if (firstLine == "LOSE\n")
            pageType = LOSE;
        else pageType = CHOICE;
    }
    
    virtual ~Page() {}
};


#endif /* PAGE_H */

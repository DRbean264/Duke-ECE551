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
    // Inner Choices class, process the page choices,
    // like print, add choices, and get choice number
    class Choices
    {
        // this field contains (choice number, description) pairs
        std::vector<std::pair<int, std::string> > chArr;
    public:
        Choices() {}

        // print the choices information in a readable format
        void print() const {
            for (size_t i = 0; i < chArr.size(); ++i) {
                std::cout << " " << i + 1 << ". " <<
                    chArr[i].second << std::endl;
            }
        }

        // get current page's choice numbers into the results vector
        void getPageChoicesNumber(std::vector<int> &results) const {
            results = std::vector<int>();
            for (size_t i = 0; i < chArr.size(); ++i) {
                results.push_back(chArr[i].first);
            }            
        }

        // parse the input line and add new choice info
        void addChoice(std::string line) {            
            size_t colPos = line.find(':');
            if (colPos == std::string::npos) {             // if there is no colon
                ExitAbnormal("The choice line should contain a colon.");
            }
            int pageNum;
            // check the validity of the number before the colon
            if (!isValidNumber(line.substr(0, colPos), &pageNum, false)) {
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
    // if true, then the number should not contain any sign before it
    // if false, then then number with sign is acceptable
    bool noSign;
// public member function
public:
    Page(std::string _filename) : filename(_filename), noSign(true) {
        parse();
    }    
    Page(std::string _filename, bool _noSign) : filename(_filename), noSign(_noSign) {
        parse();
    }
    // an interface of getting current page's choices
    std::vector<int> getPageChoicesNum() const {
        std::vector<int> results;
        choices.getPageChoicesNumber(results);
        return results;
    }
    
    int getPageType() {
        return pageType;
    }
    // print the page of requested format
    void printPage() const {
        for (size_t i = 0; i < text.size(); ++i) {
            std::cout << text[i] << '\n';
        }
        switch (pageType) {
        case WIN:
            std::cout << "\nCongratulations! You have won. Hooray!\n";
            break;
        case LOSE:
            std::cout << "\nSorry, you have lost. Better luck next time!\n";
            break;
        case CHOICE:
            std::cout << "\nWhat would you like to do?\n\n";        
            choices.print();
            break;
        default:
            ExitAbnormal("The page type should be among WIN, LOSE, CHOICE.");
            break;
        }                   
    }    

    virtual ~Page() {}
// protected member function
protected:
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

        // if the page type is WIN or LOSE, then the separator '#' should be immediately on the next line
        if (pageType == WIN || pageType == LOSE) {
            std::getline(inFile, line);
            if (line.size() == 0 || line[0] != '#') {
                ExitAbnormal("The content format of the WIN/LOSE page is wrong.");
            }
        } else {   // deal with the choice lines
            while (true) {
                choices.addChoice(line);
                if (!std::getline(inFile, line))
                    ExitAbnormal("The separator '#' doesn't exist.");
                if (line.size() > 0 && line[0] == '#')
                    break;
            }            
        }
        // pass all the format checking
        // read the text
        readText(inFile);
    }
    // read the text from the file
    void readText(std::ifstream &inFile) {
        std::string line;
        while (getline(inFile, line)) {
            text.push_back(line);
        }
    }
    
    // the page file name must be in the format 'pageXXX.txt'
    void checkFilename() {
        // if the first 4 characters of the file name are not 'page'
        std::size_t fileNameStart = filename.find_last_of("/\\");
        std::string temp;
        if (fileNameStart == std::string::npos)
            temp = filename;
        else
            temp = filename.substr(fileNameStart + 1, filename.size() - 1 - fileNameStart);
        
        if (temp.find("page") != 0) {
            ExitAbnormal("The page file name should be in the format 'pageXXX.txt'");
        }
        // check if the characters after it is a valid number
        size_t dotPos = temp.find('.');
        size_t numStart = 4;
        int tempPageNum;
        if (!isValidNumber(temp.substr(numStart, dotPos - numStart), &tempPageNum, noSign)) {
            ExitAbnormal("The number after page should be a valid number and strictly greater than 0.");
        }
        // pass all the format checking
        pageNum = tempPageNum;
    }
    
    // we can infer the page type from the first line
    // set the correcponding page type
    void setPageType(std::string firstLine) {
        if (firstLine == "WIN")
            pageType = WIN;
        else if (firstLine == "LOSE")
            pageType = LOSE;
        else pageType = CHOICE;
    }        
};


#endif /* PAGE_H */

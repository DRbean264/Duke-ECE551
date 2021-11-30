#ifndef STORY_H
#define STORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <deque>
#include <assert.h>
#include "page.h"
#include "utils.h"

class Story
{
    std::string dirName;
    int numOfPage;
    int curPageNum;
    std::vector<std::vector<int> > refedPage;
    std::vector<int> winPage;
    std::vector<int> losePage;
protected:
    std::string getPageFileName() {
        std::stringstream ss;
        ss << dirName << "/page" << curPageNum << ".txt";
        return ss.str();
    }

    bool checkFileExist(std::string pageName) {
        std::ifstream inFile(pageName.c_str());
        return inFile.good();
    }
    
    void checkPages() {
        curPageNum = 1;
        std::string pageName = getPageFileName();
        // if page1.txt doesn't exist
        if (!checkFileExist(pageName)) {
            ExitAbnormal("Can not find page1.txt in this directory.");
        }
        
        while (true) {
            // check if the page can be constructed successfully
            Page p(pageName);
            ++numOfPage;
            refedPage.push_back(p.getPageChoicesNum());
            if (p.getPageType() == WIN) { // if the page is WIN page
                winPage.push_back(curPageNum);
            } else if (p.getPageType() == LOSE) { // if the page is LOSE page
                losePage.push_back(curPageNum);
            }
            
            // to the next page
            ++curPageNum;
            pageName = getPageFileName();
            // if page after page1.txt doesn't exist, not an error, but the end of the story
            if (!checkFileExist(pageName)) {
                curPageNum = 1;
                break;
            }            
        }
    }

    void checkStoryLogic() {
        std::set<int> refedPageSet;
        for (size_t i = 0; i < refedPage.size(); ++i) {
            for (size_t j = 0; j < refedPage[i].size(); ++j) {
                refedPageSet.insert(refedPage[i][j]);
            }            
        }
        // Every page that is referenced by a choice is valid
        for (std::set<int>::const_iterator it = refedPageSet.begin(); it != refedPageSet.end(); ++it) {
            if (*it <= 0 || *it > numOfPage)
                ExitAbnormal("Every page that is referenced by a choice should be valid");            
        }
        // Every page (except page 1) is referenced by at least one *other* page's choices.
        for (int i = 2; i <= numOfPage; ++i) {
            if (refedPageSet.find(i) == refedPageSet.end())
                ExitAbnormal("Every page (except page 1) should be referenced by at least one *other* page's choices.");
        }
        // Story should contain at least one WIN and one LOSE page
        if (winPage.size() == 0 || losePage.size() == 0)
            ExitAbnormal("A story should contain at least one WIN and one LOSE page.");
    }
    
    void checkValidity() {
        // first check all the pages
        // e.g. check the existence of page1.txt, the content of all the pages
        // at the same time, set the member fields correctly if all the pages are valid
        checkPages();
        // check the story logic
        checkStoryLogic();                
    }
    
    // Request the user to input a choice
    // would only output 0 when user press CTRL-D, namely end of file
    int getUserChoice() {
        int numOfChoices = refedPage[curPageNum - 1].size();
        std::string userInput;
        std::cin >> userInput;
        int choiceId;
        while (true) {
            // if the user input EOF
            if (std::cin.eof()) {
                ExitAbnormal("Cannot read from stdin.");
            }                
            if (isValidNumber(userInput, &choiceId, false) && (choiceId >= 1 && choiceId <= numOfChoices)) {
                break;
            }
            std::cerr << "That is not a valid choice, please try again\n";
            std::cin >> userInput;
        }
        
        return refedPage[curPageNum - 1][choiceId - 1];
    }

    int getChoiceNum(int curPage, int nextPage) const {
        for (size_t i = 0; i < refedPage[curPage - 1].size(); ++i) {
            if (refedPage[curPage - 1][i] == nextPage) {
                return i + 1;
            }
        }
        return 0;
    }
    
    void printCycleFreeWin(std::vector<int> &result) const {
        for (size_t i = 1; i < result.size(); ++i) {
            std::cout << result[i - 1] << "(" << getChoiceNum(result[i - 1], result[i])
                      << "),";
        }
        std::cout << result.back() << "(win)\n";
    }   

        bool isLosePage(int pageNum) {
        for (size_t i = 0; i < losePage.size(); ++i) {
            if (pageNum == losePage[i])
                return true;
        }
        return false;
    }
    
    bool isWinPage(int pageNum) {
        for (size_t i = 0; i < winPage.size(); ++i) {
            if (pageNum == winPage[i])
                return true;
        }
        return false;
    }

    
public:
    Story(std::string _dirName)
        : dirName(_dirName), numOfPage(0), curPageNum(0) {
        checkValidity();
    }
    
    void start() {
        // display from the first page of the story
        curPageNum = 1;
        std::string pageName;
        
        while (true) {
            // display current page
            pageName = getPageFileName();
            Page p(pageName);
            p.printPage();
            // if reach the win/lose page, exit success
            if (p.getPageType() == WIN || p.getPageType() == LOSE)
                break;
            
            // get choice from user
            curPageNum = getUserChoice();
            // additionally, if reach the EOF, exit success
            if (curPageNum == 0)
                break;
        }
    }

    // calculate the story depth and print it out
    void calculateStoryDepth() {
        std::vector<std::vector<int> > result(refedPage.size() + 1, std::vector<int>(1, -1));
        graphSearch<myQueue<std::vector<int> >, BFS>(refedPage, 1, result);

        for (size_t i = 1; i < result.size(); ++i) {
            if (result[i][0] != -1)
                std::cout << "Page " << i << ':'
                          << result[i][0] << '\n';
            else
                std::cout << "Page " << i << " is not reachable\n";
        }
    }
     
    void calculateCycleFreeWin() {
        std::vector<std::vector<int> > result;
        graphSearch<myStack<std::vector<int> >, DFS>(refedPage, 1, result);
        
        bool winnible = false;
        for (size_t i = 0; i < result.size(); ++i) {
            if (isWinPage(result[i].back())) {
                winnible = true;
                printCycleFreeWin(result[i]);
            }
        }
        if (!winnible)
            std::cout << "This story is unwinnable!\n";
    }
            
    void printStoryInfo() {
        std::cout << "Number of pages in this story: " << numOfPage << '\n';
        std::cout << "Page choices:\n";
        for (size_t i = 0; i < refedPage.size(); ++i) {
            for (size_t j = 0; j < refedPage[i].size(); ++j) {
                std::cout << refedPage[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << "\nWin page is/are:\n";
        for (size_t i = 0; i < winPage.size(); ++i) {
            std::cout << winPage[i] << ' ';
        }
        std::cout << "\nLose page is/are:\n";
        for (size_t i = 0; i < winPage.size(); ++i) {
            std::cout << losePage[i] << ' ';
        }
        std::cout << std::endl;
    }
    
    virtual ~Story() {}
};

#endif /* STORY_H */

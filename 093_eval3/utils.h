#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <stack>
#include <queue>

#define BFS 1
#define DFS 2

template<typename T>
class myStack : public std::stack<T>
{
public:
    myStack<T>() {}

    T pop() {
        T temp = std::stack<T>::top();
        std::stack<T>::pop();
        return temp;
    }
};

template<typename T>
class myQueue : public std::queue<T>
{
public:
    myQueue<T>() {}

    T pop() {
        T temp = std::queue<T>::front();
        std::queue<T>::pop();
        return temp;
    }
};


void ExitAbnormal(const char *msg) {
    std::cerr << "ERROR: " << msg << std::endl;
    exit(EXIT_FAILURE);
}

bool isValidNumber(const std::string &line, int *pageNum, bool noSign) {
    if (line.size() == 0) {
        return false;
    }
    std::stringstream ss(line);
    ss >> *pageNum;
    ss.clear();
    std::string rest;
    ss >> rest;
    // the page number should be strictly greater than 0 and should only be valid number
    if (*pageNum <= 0 || rest.size() > 0)
        return false;
    // if noSign is set to be true, then the number with a sign symbol (+/-) before it is not accepted
    if (noSign && (line[0] < '0' || line[0] > '9')) {
        return false;
    }
    return true;
}

template<typename T, int mode>
void updateResult(std::vector<T> &result, const std::vector<int> &curPath) {
    if (mode == BFS) {
        result[curPath.back()] = std::vector<int>(1, curPath.size() - 1);
    } else if (mode == DFS) {
        result.push_back(curPath);        
    }    
}

template<typename Container, int mode>
void graphSearch(const std::vector<std::vector<int> > &adjList, int from, std::vector<std::vector<int> > &result) {
    std::set<int> visited;
    Container con;
    con.push(std::vector<int>(1, from));

    while (!con.empty()) {
        std::vector<int> curPath = con.pop();
        if (mode == DFS)
            visited = std::set<int>(curPath.begin(), curPath.end() - 1);
        int curNode = curPath.back();
        // if this node is unvisited
        if (visited.find(curNode) == visited.end()) {
            visited.insert(curNode);
            // only when the last page is win/lose should we put the path into result
            // or the is calculating story depth
            if (mode == BFS || (mode == DFS && adjList[curNode - 1].size() == 0))
                updateResult<std::vector<int>, mode>(result, curPath);
            
            for (size_t i = 0; i < adjList[curNode - 1].size(); ++i) {
                curPath.push_back(adjList[curNode - 1][i]);
                con.push(curPath);
                curPath.pop_back();
            }            
        }
    }    
}


#endif /* UTILS_H */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

void ExitAbnormal(const char *msg) {
    std::cerr << "ERROR: " << msg << std::endl;
    exit(EXIT_FAILURE);
}

bool isValidNumber(const std::string &line, int *pageNum) {
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
    return true;
}

#endif /* UTILS_H */

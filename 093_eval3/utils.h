#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>

void ExitAbnormal(const char *msg) {
    std::cerr << "ERROR: " << msg << std::endl;
    exit(EXIT_FAILURE);
}

#endif /* UTILS_H */

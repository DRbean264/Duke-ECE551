#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
    if (sym > 256 ) {
        s << "INV";
    }
    else if (sym == 256) {
        s << "EOF";
    }
    else if (isprint(sym)) {
        char c = sym;
        s << "'" << c << "'";
    }
    else {
        std::streamsize w = s.width(3);
        s << std::hex << sym << std::dec;
        s.width(w);
    }
}
uint64_t * readFrequencies(const char * fname) {
    std::ifstream inFile(fname, std::ifstream::in);
    if (!inFile.good()) {
        std::cerr << "Can not open the file.\n";
        exit(EXIT_FAILURE);
    }        
    uint64_t *freq = new uint64_t[257]();

    int ch;
    while ((ch = inFile.get()) != -1) {
        freq[ch] += 1;
    }
    freq[256] = 1;

    return freq;
}

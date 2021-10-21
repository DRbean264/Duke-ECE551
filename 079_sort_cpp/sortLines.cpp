#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

template<typename T>
void sortAndPrintFromFile(T &s) {
    vector<string> lines;
    string line;    
    while (getline(s, line)) {
        cout << "EOF bit: " << s.eof() << '\n';
        lines.push_back(line);
    }
    cout << "EOF bit: " << s.eof() << '\n';
    
    sort(lines.begin(), lines.end());
    // print the strings
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << lines[i] << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {            // read from stdin
        sortAndPrintFromFile<istream>(cin);
    } else if (argc >= 1){      // if have files
        for (size_t i = 1; i < (size_t)argc; ++i) {
            ifstream f(argv[i]);
            if (!f) {
                cerr << "Fail to open the file " << argv[i] << '\n';
                exit(EXIT_FAILURE);
            }
            sortAndPrintFromFile<ifstream>(f);
            f.close();
        }
    }
    return 0;
}

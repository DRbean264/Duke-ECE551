#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
using namespace std;
template<typename T>
class Matrix
{
    int numRows;
    int numColumns;
    vector<vector<T> > rows;
public:
    Matrix()
        : numRows(0), numColumns(0), rows(vector<vector<T> >()) {        
    }

    Matrix(int r, int c)
        : numRows(r), numColumns(c), rows(vector<vector<T> >(r, vector<T>(c, T()))) {        
    }
    
    ~Matrix() {};

    Matrix(const Matrix<T> &rhs)
        : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {
    }

    Matrix &operator=(const Matrix<T> &rhs) {
        rows = rhs.rows;
        numRows = rhs.numRows;
        numColumns = rhs.numColumns;
        return *this;
    }

    int getRows() const {
        return numRows;
    }

    int getColumns() const {
        return numColumns;
    }

    const vector<T> &operator[](int index) const {
        assert(index >= 0 && index < numRows);
        return rows[index];
    }
    vector<T> &operator[](int index){
        assert(index >= 0 && index < numRows);
        return rows[index];
    }
    
    bool operator==(const Matrix<T> &rhs) const {
        return rows == rhs.rows;        
    }

    Matrix operator+(const Matrix<T> &rhs) const {
        assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
        Matrix mat(numRows, numColumns);
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numColumns; ++j) {
                mat[i][j] = rows[i][j] + rhs.rows[i][j];
            }
        }
        return mat;
    }    
};

template<typename T>
ostream &operator<<(ostream &s, const vector<T> &rhs) {
    s << "{";
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (i != 0) {
            s << ", ";
        }
        s << rhs[i];
    }
    s << "}";
    return s;
}

template<typename T>
ostream &operator<<(ostream &s, const Matrix<T> &rhs) {
    s << "[ ";
    for (int i = 0; i < rhs.getRows(); ++i) {
        if (i != 0) {
            s << ",\n";
        }
        s << rhs[i];
    }
    s << " ]";
    return s;
}

#endif

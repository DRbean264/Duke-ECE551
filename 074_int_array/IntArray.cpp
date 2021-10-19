#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray()
    : data(NULL), numElements(0) {}

IntArray::IntArray(int n) {
    if (n == 0) {
        IntArray();
    } else {
        numElements = n;
        data = new int[numElements];
    }
}

IntArray::IntArray(const IntArray & rhs)
    : data(NULL), numElements(rhs.numElements) {
    if (numElements != 0) {
        data = new int[numElements];
        for (int i = 0; i < rhs.numElements; ++i) {
            data[i] = rhs.data[i];
        }
    }    
}

IntArray::~IntArray() {
    delete [] data;    
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete [] data;
    numElements = rhs.numElements;
    data = NULL;
    if (numElements != 0) {
        data = new int[numElements];
        for (int i = 0; i < numElements; ++i) {
            data[i] = rhs.data[i];
        }
    }    
    return *this;
}

const int & IntArray::operator[](int index) const {
    assert(index >=0 && index < numElements);    
    return data[index];
}

int & IntArray::operator[](int index) {
    assert(index >=0 && index < numElements);    
    return data[index];
}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    if (numElements != rhs.numElements) {
        return false;
    }
    for (int i = 0; i < numElements; ++i) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
    return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
    s << '{';
    for (int i = 0; i < rhs.size() - 1; ++i) {
        s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1] << "}";
    return s;
}

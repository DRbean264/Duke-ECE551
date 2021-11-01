#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}

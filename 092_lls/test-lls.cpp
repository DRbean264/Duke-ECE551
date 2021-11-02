#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;

class Tester {
public:
    // testing for default constructor is done for you
    void testDefCtor() {
        IntList il;
        assert(il.head == NULL); // test 1
        assert(il.tail == NULL);
        assert(il.getSize() == 0);
    }
    // example of another method you might want to write
    void testAddFront() {
        IntList il0;
        il0.addFront(0);
        assert(il0.head == il0.tail && il0.head != NULL);
        assert(il0.getSize() == 1); // test 4
        assert(il0[0] == 0);     // test 2
        assert(il0.head->next == NULL && il0.head->prev == NULL);

        IntList il1;
        il1.addFront(3);
        assert(il1.head == il1.tail && il1.head != NULL);
        assert(il1.getSize() == 1);
        assert(il1[0] == 3);
        assert(il1.head->next == NULL && il1.head->prev == NULL);

        IntList il2;
        il2.addFront(-1);
        assert(il2.head == il2.tail && il2.head != NULL);
        assert(il2.getSize() == 1);
        assert(il2[0] == -1);
        assert(il2.head->next == NULL && il2.head->prev == NULL);

        IntList il3;
        il3.addFront(1);
        il3.addFront(-1);
        il3.addFront(0);
        IntList::Node *curr = il3.head;
        assert(curr->data == 0); // test 5
        assert(curr->next != NULL && curr->prev == NULL);
        curr = curr->next;
        assert(curr->data == -1);
        assert(curr->next != NULL && curr->prev != NULL); // test 3
        assert(curr->prev->data == 0);
        curr = curr->next;
        assert(curr->data == 1);
        assert(curr->next == NULL && curr->prev != NULL);
        assert(curr->prev->data == -1);
        assert(il3.tail == curr);        
        assert(il3.getSize() == 3);        
    }
    void testAddBack() {
        IntList il0;
        il0.addBack(0);
        assert(il0.head == il0.tail && il0.head != NULL); // test 8
        assert(il0.getSize() == 1);
        assert(il0[0] == 0);    // test 6
        assert(il0.head->next == NULL && il0.head->prev == NULL);

        IntList il1;
        il1.addBack(3);
        assert(il1.head == il1.tail && il1.head != NULL);
        assert(il1.getSize() == 1);
        assert(il1[0] == 3);
        assert(il1.head->next == NULL && il1.head->prev == NULL);

        IntList il2;
        il2.addBack(-1);
        assert(il2.head == il2.tail && il2.head != NULL);
        assert(il2.getSize() == 1);
        assert(il2[0] == -1);
        assert(il2.head->next == NULL && il2.head->prev == NULL);

        IntList il3;
        il3.addBack(1);
        il3.addBack(-1);
        il3.addBack(0);
        IntList::Node *curr = il3.head;
        assert(curr->data == 1);                          // test 9
        assert(curr->next != NULL && curr->prev == NULL); // test 7
        curr = curr->next;
        assert(curr->data == -1);
        assert(curr->next != NULL && curr->prev != NULL);
        assert(curr->prev->data == 1);
        curr = curr->next;
        assert(curr->data == 0);
        assert(curr->next == NULL && curr->prev != NULL);
        assert(curr->prev->data == -1);
        assert(il3.tail == curr);        
        assert(il3.getSize() == 3);        
    }
    void testCopyCtor() {
        IntList il0;
        il0.addBack(1);
        il0.addBack(-1);
        il0.addBack(0);
        
        IntList il1(il0);
        assert(il0.getSize() == 3);
        assert(il1.getSize() == 3); // test 10
        IntList::Node *curr0 = il0.head;
        IntList::Node *curr1 = il1.head;
        assert(curr1->data == 1 && curr1->prev == NULL && curr1->next != NULL);
        assert(curr0 != curr1); // test 11
        curr1 = curr1->next;
        curr0 = curr0->next;
        assert(curr1->data == -1 && curr1->prev != NULL && curr1->next != NULL);
        assert(curr1->prev->data == 1);
        assert(curr0 != curr1);
        assert(curr0->prev != curr1->prev);
        curr1 = curr1->next;
        curr0 = curr0->next;
        assert(curr1->data == 0 && curr1->prev != NULL && curr1->next == NULL);
        assert(curr1->prev->data == -1);
        assert(curr0 != curr1);
        assert(curr0->prev != curr1->prev);
        assert(il1.tail == curr1);

        IntList il2;
        IntList il3(il2);
        assert(il3.head == NULL && il3.tail == NULL);
        assert(il3.getSize() == 0);
    }
    void testAssignOp() {
        IntList il0;
        il0.addBack(1);
        il0.addBack(-1);
        il0.addBack(0);
        il0 = il0;
        assert(il0.getSize() == 3);
        assert(il0[0] == 1 && il0[1] == -1 && il0[2] == 0);
        assert(il0.head->data == 1);
        assert(il0.tail->data == 0);

        IntList il1;        
        il1.addBack(4);
        il1.addBack(-90);
        il1.addBack(213);
        il1.addBack(32);
        il1 = il0;
        assert(il1.getSize() == 3);
        assert(il1[0] == 1 && il1[1] == -1 && il1[2] == 0);
        assert(il1.head->data == 1);
        assert(il1.tail->data == 0);
    }
    void testRemove() {
        IntList il0;
        il0.addBack(3);
        il0.addBack(2);
        il0.addBack(0);
        il0.addBack(34);
        il0.addBack(3);

        assert(il0.remove(3));
        assert(il0.getSize() == 4); // test 19
        assert(il0[0] == 2);
        assert(il0.head != NULL && il0.tail != NULL);
        assert(il0.head->data == 2);
        assert(il0.tail->data == 3);
        assert(il0.head->prev == NULL); // test 20
        assert(il0[0] == 2);
        assert(il0[1] == 0);
        assert(il0[2] == 34);
        assert(il0[3] == 3);        

        IntList il1;
        il1.addBack(3);        

        assert(il1.remove(3));
        assert(il1.getSize() == 0); // test 17
        assert(il1.head == NULL && il1.tail == NULL); // test 18

        IntList il2;
        il2.addBack(3);        
        il2.addBack(9);        
        il2.addBack(10);        
        il2.addBack(1);        
        il2.addBack(3289);        

        assert(il2.remove(348) == false);
        assert(il2.getSize() == 5);
        assert(il2.remove(3289));
        assert(il2.getSize() == 4); // test 22
        assert(il2.head != NULL && il2.tail != NULL);
        assert(il2.tail->data == 1); // test 21
        assert(il2.head->data == 3);
        assert(il2.tail->prev != NULL);
        assert(il2[0] == 3);
        assert(il2[1] == 9);
        assert(il2[2] == 10);
        assert(il2[3] == 1);
        
        IntList il3;
        il3.addBack(3);        
        il3.addBack(9);        
        il3.addBack(10);        
        il3.addBack(1);        
        il3.addBack(3289);        

        assert(il3.remove(348) == false);
        assert(il3.getSize() == 5);
        assert(il3.remove(3));
        assert(il3.getSize() == 4);
        assert(il3.head != NULL && il3.tail != NULL);
        assert(il3.tail->data == 3289);
        assert(il3.head->data == 9);
        assert(il3[0] == 9);
        assert(il3[1] == 10);
        assert(il3[2] == 1);
        assert(il3[3] == 3289);
        assert(il3.head->prev == NULL);
        assert(il3.tail->prev != NULL);
        
        IntList il4;
        il4.addBack(3);        
        il4.addBack(9);        
        il4.addBack(10);        
        il4.addBack(1);        
        il4.addBack(3289);        

        assert(il4.remove(348) == false);
        assert(il4.getSize() == 5);
        assert(il4.remove(10));
        assert(il4.getSize() == 4); // test 23
        assert(il4.head != NULL && il4.tail != NULL);
        assert(il4.tail->data == 3289);
        assert(il4.head->data == 3);
        assert(il4[0] == 3);
        assert(il4[1] == 9);
        assert(il4[2] == 1);
        assert(il4[3] == 3289);
        assert(il4.head->next->next->prev != NULL);        
        
        IntList il5;
        il5.addBack(3);        
        il5.addBack(9);        
        il5.addBack(10);        
        il5.addBack(1);        
        il5.addBack(3289);        

        assert(il5.remove(3));
        assert(il5.head->prev == NULL);
        assert(il5.getSize() == 4);
        assert(il5.remove(9));
        assert(il5.head->prev == NULL);
        assert(il5.getSize() == 3);
        assert(il5.remove(10));
        assert(il5.head->prev == NULL);
        assert(il5.getSize() == 2);
        assert(il5.remove(1));
        assert(il5.head->prev == NULL);
        assert(il5.getSize() == 1);
        assert(il5.remove(3289));
        assert(il5.getSize() == 0);
        assert(il5.head == NULL && il5.tail == NULL);

        IntList il6;
        assert(il6.remove(5) == false);

        IntList il7;
        il7.addFront(4);
        il7.addFront(5);
        il7.addFront(3);
        il7.addFront(3);
        il7.addFront(8);
        il7.addFront(9);

        assert(il7.remove(3));
        assert(il7.getSize() == 5);
        assert(il7.head->next->next->data == 3);
        assert(il7.head->next->next->prev != NULL);
        assert(il7.head->next->next->prev->data = 8);
    }
};

int main(void) {
    Tester t;
    t.testDefCtor();
    t.testAddFront();
    t.testAddBack();
    t.testCopyCtor();
    t.testAssignOp();
    t.testRemove();
    return EXIT_SUCCESS;
}

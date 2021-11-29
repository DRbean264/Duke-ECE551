#include <iostream>
#include <cstdlib>
using namespace std;

class A {
public:
	int x;
	A() :x(0) {  }	
};

class B: public virtual A {};	
class C: virtual public A {
public:
    int x;
    C(int _x) : x(_x) {}
};

class D: public B, C {
public:
    D() : C(1) {}
    void print() {
        cout << x << endl;
    }
};	

int main()
{
    D aD;
    aD.print();
    return 0;
}

#include <iostream>
#include "bstmap.h"
using namespace std;

int main()
{
    try {
        BstMap<int, int> bm;
        bm.add(1, 2);
        bm.add(0, 6);
        bm.add(3, 4);
        bm.add(-1, 99);
        bm.add(2, 7);
        bm.add(1, 34);
        bm.add(80, 3);
        bm.add(4, 90);
        bm.add(-1, 98);
        cout << "The tree is now: \n";
        bm.printBstMap();
        cout << '\n';

        cout << "Looking for key -1: " << bm.lookup(-1) << endl;
        cout << "Looking for key 0: " << bm.lookup(0) << endl;
        cout << "Looking for key 2: " << bm.lookup(2) << endl;
        cout << "Looking for key 4: " << bm.lookup(4) << endl;
        // cout << "Looking for key 5: " << bm.lookup(5) << endl;
        cout << "Looking for key 80: " << bm.lookup(80) << endl;

        bm.remove(0);
        cout << "After removing 0, the tree is now: \n";
        bm.printBstMap();
        cout << '\n';

        bm.remove(-1);
        cout << "After removing -1, the tree is now: \n";
        bm.printBstMap();
        cout << '\n';

        bm.remove(3);
        cout << "After removing 3, the tree is now: \n";
        bm.printBstMap();
        cout << '\n';

    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
    
    return 0;
}

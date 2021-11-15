#include "node.h"
#include <assert.h>

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
    if (sym != NO_SYM) {
        assert(left == NULL && right == NULL);
        theMap[sym] = b;
        return;
    }

    assert(left  && right);
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
}

#include "node.h"

Node * buildTree(uint64_t * counts) {
    if (counts == NULL)
        return NULL;
    
    priority_queue_t pq;
    for (size_t i = 0; i < 257; ++i) {
        if (counts[i] != 0) {
            pq.push(new Node(i, counts[i]));
        }
    }

    while (pq.size() != 1) {
        // fetch two elements
        Node *first = pq.top();
        pq.pop();
        Node *second = pq.top();
        pq.pop();
        Node *comb = new Node(first, second);
        pq.push(comb);
    }
    return pq.top();
}  

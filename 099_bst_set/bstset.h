#ifndef BSTSET_H
#define BSTSET_H

#include <iostream>
#include <algorithm>
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
private:
    class Node {
    public:
        T key;
        Node *left;
        Node *right;
        Node(T _key)
            : key(_key), left(NULL), right(NULL) {}
        Node(T _key, Node *_left, Node *_right)
            : key(_key), left(_left), right(_right) {}
    };

    Node *addHelper(Node *curr, const T &key) {
        // base cases
        if (!curr) {
            Node *newNode = new Node(key);
            return newNode;
        }
        if (curr->key == key) {
            return curr;
        }

        // recursive call
        if (key < curr->key) {
            curr->left = addHelper(curr->left, key);
        } else {
            curr->right = addHelper(curr->right, key);
        }
        return curr;
    }

    bool containsHelper (Node *curr, const T &key) const {
        // base cases
        if (!curr) {
            return false;
        }
        if (curr->key == key) {
            return true;
        }

        // recursive call
        if (key < curr->key) {
            return containsHelper(curr->left, key);
        } else {
            return containsHelper(curr->right, key);
        }
    }

    virtual Node *removeHelper(Node *curr, const T& key) {
        if (!curr)              // not find the key
            return curr;
        if (curr->key == key) { // find the key
            if (!curr->left) { // if not have left child
                Node *rightChild = curr->right;
                delete curr;
                return rightChild;
            } else if (!curr->right) { // if not have right child
                Node *leftChild = curr->left;
                delete curr;
                return leftChild;
            } else {            // if have both children
                // find the left-most node of the right child
                Node **temp = &curr->right;
                while ((*temp)->left) {
                    temp = &(*temp)->left;
                }
                curr->key = (*temp)->key;
                Node *temp2 = (*temp)->right;
                delete *temp;
                *temp = temp2;
                return curr;
            }
        }

        if (key < curr->key)
            curr->left = removeHelper(curr->left, key);
        else
            curr->right = removeHelper(curr->right, key);
        return curr;
    }

    void destructHelper(Node *curr) {
        if (!curr)
            return;
        destructHelper(curr->left);
        destructHelper(curr->right);
        delete curr;
    }

    Node *copyHelper(const Node *rootCopy) {
        if (!rootCopy)
            return NULL;
        Node *newLeft = copyHelper(rootCopy->left);
        Node *newRight = copyHelper(rootCopy->right);
        Node *curr = new Node(rootCopy->key, newLeft, newRight);
        return curr;
    }
    
    Node *root;
public:
    BstSet<T>() : root(NULL) {}
    BstSet<T>(const BstSet &rhs) : root(NULL) {
        root = copyHelper(rhs.root);
    }
    BstSet<T> &operator=(const BstSet &rhs) {
        if (this != &rhs) {
            BstSet<T> temp(rhs);
            std::swap(temp.root, root);
        }
        return *this;
    }
    
    virtual void add(const T &key) {
        root = addHelper(root, key);        
    }

    virtual bool contains(const T &key) const {
        return containsHelper(root, key);
    }

    virtual void remove(const T& key) {
        root = removeHelper(root, key);
    }

    virtual ~BstSet<T>() {
        destructHelper(root);
    }    
};

#endif /* BSTSET_H */

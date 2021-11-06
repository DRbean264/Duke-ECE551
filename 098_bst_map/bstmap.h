#ifndef BSTMAP_H
#define BSTMAP_H

#include <iostream>
#include <algorithm>
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
private:
    class Node {
    public:
        K key;
        V value;
        Node *left;
        Node *right;
        Node(K _key, V _value)
            : key(_key), value(_value), left(NULL), right(NULL) {}
        Node(K _key, V _value, Node *_left, Node *_right)
            : key(_key), value(_value), left(_left), right(_right) {}
    };

    Node *addHelper(Node *curr, const K &key, const V &value) {
        // base cases
        if (!curr) {
            Node *newNode = new Node(key, value);
            return newNode;
        }
        if (curr->key == key) {
            curr->value = value;
            return curr;
        }

        // recursive call
        if (key < curr->key) {
            curr->left = addHelper(curr->left, key, value);
        } else {
            curr->right = addHelper(curr->right, key, value);
        }
        return curr;
    }

    const V &lookupHelper (Node *curr, const K &key) const {
        // base cases
        if (!curr) {
            throw std::invalid_argument("The key is not found");
        }
        if (curr->key == key) {
            return curr->value;
        }

        // recursive call
        if (key < curr->key) {
            return lookupHelper(curr->left, key);
        } else {
            return lookupHelper(curr->right, key);
        }
    }

    virtual Node *removeHelper(Node *curr, const K& key) {
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
                Node *temp = curr->right;
                Node *prev = NULL;
                while (temp->left) {
                    prev = temp;
                    temp = temp->left;
                }
                curr->key = temp->key;
                curr->value = temp->value;
                if (prev) 
                    prev->left = temp->right;                    
                else
                    curr->right = temp->right;
                delete temp;                                
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
        Node *curr = new Node(rootCopy->key, rootCopy->value, newLeft, newRight);
        return curr;
    }
    
    Node *root;
public:
    BstMap<K, V>() : root(NULL) {}
    BstMap<K, V>(const BstMap &rhs) : root(NULL) {
        root = copyHelper(rhs.root);
    }
    BstMap<K, V> &operator=(const BstMap &rhs) {
        if (this != &rhs) {
            BstMap<K, V> temp(rhs);
            std::swap(temp.root, root);
        }
        return *this;
    }
    
    virtual void add(const K &key, const V &value) {
        root = addHelper(root, key, value);        
    }

    virtual const V &lookup(const K &key) const throw(std::invalid_argument) {
        return lookupHelper(root, key);
    }

    virtual void remove(const K& key) {
        root = removeHelper(root, key);
    }

    virtual ~BstMap<K, V>() {
        destructHelper(root);
    }

    void printBstMap() {
        inOrderTraversal(root);
    }
    
    void inOrderTraversal(Node *root) {
        if (!root)
            return;
        inOrderTraversal(root->left);
        std::cout << "(" << root->key << ", " << root->value
                  << ") ";
        inOrderTraversal(root->right);
    }
};

#endif /* BSTMAP_H */

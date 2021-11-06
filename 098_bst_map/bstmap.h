#ifndef BSTMAP_H
#define BSTMAP_H

#include <iostream>
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
public:
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
private:
    Node *addHelper(Node *root, const K &key, const V &value) {
        // base cases
        if (!root) {
            Node *newNode = new Node(key, value);
            return newNode;
        }
        if (root->key == key) {
            root->value = value;
            return root;
        }

        // recursive call
        if (key < root->key) {
            root->left = addHelper(root->left, key, value);
        } else {
            root->right = addHelper(root->right, key, value);
        }
        return root;
    }

    const V &lookupHelper (Node *root, const K &key) const {
        // base cases
        if (!root) {
            throw std::invalid_argument("The key is not found");
        }
        if (root->key == key) {
            return root->value;
        }

        // recursive call
        if (key < root->key) {
            return lookupHelper(root->left, key);
        } else {
            return lookupHelper(root->right, key);
        }
    }

    virtual Node *removeHelper(Node *root, const K& key) {
        if (!root)              // not find the key
            return root;
        if (root->key == key) { // find the key
            if (!root->left) { // if not have left child
                Node *rightChild = root->right;
                delete root;
                return rightChild;
            } else if (!root->right) { // if not have right child
                Node *leftChild = root->left;
                delete root;
                return leftChild;
            } else {            // if have both children
                // find the left-most node of the right child
                Node *temp = root->right;
                Node *prev = NULL;
                while (temp->left) {
                    prev = temp;
                    temp = temp->left;
                }
                root->key = temp->key;
                root->value = temp->value;
                delete temp;
                if (prev)
                    prev->left = NULL;
                else
                    root->right = NULL;
                return root;
            }
        }

        if (key < root->key)
            root->left = removeHelper(root->left, key);
        else
            root->right = removeHelper(root->right, key);
        return root;
    }

    void destructHelper(Node *root) {
        if (!root)
            return;
        destructHelper(root->left);
        destructHelper(root->right);
        delete root;
    }
    
    Node *root;
public:
    BstMap<K, V>() : root(NULL) {}
    BstMap<K, V>(Node *_root) : root(_root) {}    
    
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

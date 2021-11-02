#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//class Tester;

class WrongIndex : public std::exception
{
    const char *msg;
public:
    WrongIndex(const char *_msg) : msg(_msg) {}
    virtual const char *what() const throw() {
        return msg;
    }
    virtual ~WrongIndex() throw() {}
};


template<typename T>
class LinkedList
{
    class Node
    {
    public:
        T data;
        Node *next;
        Node *prev;
    public:
        Node() : data(T()), next(NULL), prev(NULL) {}
        Node(const T &_data) : data(_data), next(NULL), prev(NULL) {}
        Node(const T &_data, Node *_next, Node *_prev)
            : data(_data), next(_next), prev(_prev) {}
        virtual ~Node() {}
    };
    Node *head;
    Node *tail;
public:
    LinkedList() : head(NULL), tail(NULL) {}

    LinkedList(const LinkedList &rhs)
        : head(NULL), tail(NULL) {
        Node *curr = rhs.head;
        while (curr != NULL) {
            this->addBack(curr->data);
            curr = curr->next;
        }
    }

    LinkedList &operator=(const LinkedList &rhs) {
        if (this != &rhs) {
            LinkedList temp;
            Node *curr = rhs.head;
            while (curr != NULL) {
                temp.addBack(curr->data);
                curr = curr->next;
            }

            std::swap(temp.head, head);
            std::swap(temp.tail, tail);
        }
        return *this;
    }

    ~LinkedList() {
        Node *curr = head;
        while (curr != NULL) {
            Node *nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    int getSize() const {
        Node *curr = head;
        int sz = 0;
        while (curr != NULL) {
            ++sz;
            curr = curr->next;
        }
        return sz;
    }
    
    void addFront(const T &item) {
        Node *newNode = new Node(item, head, NULL);
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == NULL) {
            tail = newNode;
        }
    }

    void addBack(const T &item) {
        Node *newNode = new Node(item, NULL, tail);
        if (tail != NULL) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == NULL) {
            head = newNode;
        }
    }

    bool remove(const T &item) {
        if (head == NULL && tail == NULL) return false;
        if (head == tail) {
            if (item == head->data) {
                delete head;
                head = NULL;
                tail = NULL;
                return true;
            } else {
                return false;
            }            
        }
            
        Node **curr = &head;
        while (*curr != NULL) {
            Node *temp = *curr;
            if (temp->data == item) {
                if (temp->next != NULL)
                    temp->next->prev = temp->prev;
                *curr = temp->next;
                if (temp == tail)
                    tail = temp->prev;
                delete temp;                
                return true;
            } else {
                curr = &temp->next;
            }
        }
        return false;
    }

    T &operator[](int index) {
        if (index < 0)
            throw WrongIndex("The index can't be less than 0!!!.");

        Node *curr = head;
        while (curr != NULL) {
            if (index == 0)
                return curr->data;
            curr = curr->next;
            --index;
        }
        throw WrongIndex("The index is out of range!!!.");
    }

    const T &operator[](int index) const {
        if (index < 0)
            throw WrongIndex("The index can't be less than 0!!!.");

        Node *curr = head;
        while (curr != NULL) {
            if (index == 0)
                return curr->data;
            curr = curr->next;
            --index;
        }
        throw WrongIndex("The index is out of range!!!.");
    }

    int find(const T &item) const {
        Node *curr = head;
        int index = 0;
        while (curr != NULL) {
            if (curr->data == item) {
                return index;
            }
            ++index;
            curr = curr->next;
        }
        return -1;
    }
        
    //friend Tester;
};


#endif

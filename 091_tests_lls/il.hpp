#ifndef IL_HPP
#define IL_HPP

#include <cstdlib>

class Tester;

class IntList {
 public:
  class Node {
   public:
    int data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(int d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  IntList();
  IntList(const IntList & rhs);
  IntList & operator=(const IntList & rhs);
  ~IntList();
  void addFront(const int & item);
  void addBack(const int & item);
  bool remove(const int & item);
  int & operator[](int index);
  const int & operator[](int index) const;
  int find(const int & item);
  int getSize() const;
  friend Tester;
};

#endif

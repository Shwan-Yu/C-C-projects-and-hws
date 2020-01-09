#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>

class myException : std::exception {
 public:
  virtual const char * notExist() const throw() {
    return "Index not exist when using [] operator";
  };
};

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * previous;
    Node() : data(0), next(NULL), previous(NULL) {}
    Node(const T & d) : data(d), next(NULL), previous(NULL) {}
    Node(const T & d, Node * nxt, Node * prv) : data(d), next(nxt), previous(prv) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * rhs_cur = rhs.head;
    while (rhs_cur != NULL) {
      addBack(rhs_cur->data);
      rhs_cur = rhs_cur->next;
    }
  };

  ~LinkedList() {
    while (head != NULL) {
      Node * cur = head->next;
      delete head;
      head = cur;
    }
    size = 0;
    tail = NULL;
  };

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      size = 0;

      Node * current = rhs.tail;
      while (current != NULL) {
        this->addFront(current->data);
        current = current->previous;
      }
      size = rhs.size;
    }
    return *this;
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->previous = head;
    }
    ++size;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->previous->next = tail;
    }
    ++size;
  }
  bool remove(const T & item) {
    if (size == 0) {
      return false;
    }
    bool isIn = false;

    if (head->data == item) {
      Node * temp = head->next;
      delete head;
      head = temp;
      if (head != NULL) {
        head->previous = NULL;
      }
      else {
        tail = NULL;
      }
      size--;
      return true;
    }

    Node * cur = head;
    while (cur->next != NULL) {
      if (cur->next->data == item) {
        isIn = true;
        break;
      }
      cur = cur->next;
    }
    if (isIn == true) {
      Node * tmp = cur->next->next;
      delete cur->next;
      cur->next = tmp;
      if (cur->next != NULL) {
        cur->next->previous = cur;
      }
      else {
        tail = cur;
      }
      size--;
    }
    return isIn;
  }

  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw myException();
    }

    Node * cur = head;
    for (int i = 0; i < index; i++) {
      cur = cur->next;
    }
    return cur->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw myException();
    }

    Node * cur = head;
    for (int i = 0; i < index; i++) {
      cur = cur->next;
    }
    return cur->data;
  }

  int find(const T & item) const {
    if (size == 0) {
      return -1;
    }
    Node * cur = head;
    for (int i = 0; i < size; i++) {
      if (cur->data == item) {
        return i;
      }
      cur = cur->next;
    }

    return -1;
  }
  int getSize() const { return size; }
};

#endif

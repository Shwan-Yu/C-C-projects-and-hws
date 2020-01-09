#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL){};
    Node(const T & k) : key(k), left(NULL), right(NULL){};
  };

 private:
  Node * root;

  Node * copyHelper(Node * cur) {
    if (cur == NULL) {
      return NULL;
    }
    Node * root = new Node(cur->key);
    root->left = copyHelper(cur->left);
    root->right = copyHelper(cur->right);
    return root;
  }

  Node * addHelper(Node * cur, const T & key) {
    if (cur == NULL) {
      Node * ans = new Node(key);
      return ans;
    }

    else {
      if (cur->key == key) {
        cur->key = key;
      }
      else if (cur->key > key) {
        cur->left = addHelper(cur->left, key);
      }
      else {
        cur->right = addHelper(cur->right, key);
      }
    }
    return cur;
  }

  bool findHelper(Node * cur, const T & key) const {
    if (cur == NULL) {
      return false;
    }
    else {
      if (cur->key == key) {
        return true;
      }
      else if (cur->key > key) {
        return findHelper(cur->left, key);
      }
      else {
        return findHelper(cur->right, key);
      }
    }
  }

  Node * FindReplacement(Node * cur) {
    if (cur == NULL) {
      return NULL;
    }

    while (cur->left != NULL) {
      cur = cur->left;
    }
    return cur;
  }

  Node * deleteHelper(Node * cur, const T & key) {
    if (cur == NULL) {
      throw std::invalid_argument("Invalid input: key not in set.");
    }
    else {
      if (cur->key > key) {
        cur->left = deleteHelper(cur->left, key);
      }
      else if (cur->key < key) {
        cur->right = deleteHelper(cur->right, key);
      }
      else {
        Node * temp;
        if (cur->left == NULL) {
          temp = cur->right;
          delete cur;
          return temp;
        }

        else if (cur->right == NULL) {
          temp = cur->left;
          delete cur;
          return temp;
        }

        else {
          temp = FindReplacement(cur->right);
          cur->key = temp->key;
          cur->right = deleteHelper(cur->right, temp->key);
        }
      }
    }
    return cur;
  }

 public:
  BstSet() : root(NULL){};
  BstSet(const BstSet & rhs) : root(NULL) { root = copyHelper(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      Node * temp = copyHelper(rhs.root);
      destruct(root);
      root = temp;
    }
    return *this;
  }

  void destruct(Node * cur) {
    if (cur != NULL) {
      destruct(cur->left);
      destruct(cur->right);
      delete cur;
    }
  }
  virtual ~BstSet<T>() {
    destruct(root);
    root = NULL;
  }
  virtual void add(const T & key) { root = addHelper(root, key); }
  virtual bool contains(const T & key) const {
    bool canFind = findHelper(root, key);
    return canFind;
  }
  virtual void remove(const T & key) { deleteHelper(root, key); }
};

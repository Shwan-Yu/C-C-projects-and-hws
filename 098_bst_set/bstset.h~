#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    K key;
    V val;
    Node * left;
    Node * right;
    Node() : key(0), val(0), left(NULL), right(NULL){};
    Node(const K & k, const V & v) : key(k), val(v), left(NULL), right(NULL){};
  };

 private:
  Node * root;

  Node * copyHelper(Node * cur) {
    if (cur == NULL) {
      return NULL;
    }
    Node * root = new Node(cur->key, cur->val);
    root->left = copyHelper(cur->left);
    root->right = copyHelper(cur->right);
    return root;
  }

  Node * addHelper(Node * cur, const K & key, const V & value) {
    if (cur == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }

    else {
      if (cur->key == key) {
        cur->key = key;
        cur->val = value;
      }
      else if (cur->key > key) {
        cur->left = addHelper(cur->left, key, value);
      }
      else {
        cur->right = addHelper(cur->right, key, value);
      }
    }
    return cur;
  }

  Node * findHelper(Node * cur, const K & key) const throw(std::invalid_argument) {
    if (cur == NULL) {
      throw std::invalid_argument("Invalid input: key not in map.");
    }
    else {
      if (cur->key == key) {
        return cur;
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

  Node * deleteHelper(Node * cur, const K & key) {
    if (cur == NULL) {
      throw std::invalid_argument("Invalid input: key not in map.");
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
          cur->val = temp->val;
          cur->right = deleteHelper(cur->right, temp->key);
        }
      }
    }
    return cur;
  }

 public:
  BstMap() : root(NULL){};
  BstMap(const BstMap & rhs) : root(NULL) { root = copyHelper(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
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
  virtual ~BstMap<K, V>() {
    destruct(root);
    root = NULL;
  }
  virtual void add(const K & key, const V & value) { root = addHelper(root, key, value); }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * cur = findHelper(root, key);
    return cur->val;
  }
  virtual void remove(const K & key) { deleteHelper(root, key); }
};

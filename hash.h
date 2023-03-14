#ifndef _HASH_HPP_
#define _HASH_HPP_

#include <vector>
#include "song.h"

template <typename K, typename V>
struct Node {
  K key;            // Artist name
  V value;          // Song object
  Node<K, V> *next; // next node/song

  Node(K k, V val) {
    this->key = k;
    this->value = val;
    this->next = nullptr;
  }
};

template <typename K, typename V>
class SeparateChaningHash {
private:
  Node<K, V> **array;
  size_t qty;
  size_t capacity;
  size_t totalQty;

public:
  SeparateChaningHash() {
    capacity = 100;
    qty = 0;
    totalQty = 0;
    array = new Node<K, V> *[capacity];

    for (size_t i = 0; i < capacity; ++i) {
      array[i] = 0;
    }
  }

  // delete memory
  ~SeparateChaningHash() {
    delete[] array;
  }

  // get size
  size_t getSize() {
    return qty;
  }

  // get size
  size_t getTotalSize() {
    return totalQty;
  }

  // check if it is empty
  bool empty() {
    return qty == 0;
  }

  // find element position
  size_t getPossition(K key) {
    size_t index = std::hash<K>{}(key) % capacity;

    // if index position is not empty
    if (array[index] != NULL) {
      // check if element exists in the linked list
      for (Node<K, V> *x = array[index]; x != nullptr; x = x->next)
        if (key == x->key)
          return index;
    }
    return -1;
  }

  // check if table contains the key
  bool contains(K key) {
    if (getPossition(key) != (size_t)-1) {
      return true;
    }
    return false;
  }

  // insert a new element/song
  void put(K key, V value) {
    qty++;

    // resize the table if quantity is greater than half
    if (qty >= capacity / 2)
      resize(2 * capacity); // resize by 2

    // hash the key
    size_t index = std::hash<K>{}(key) % capacity;

    // create a new node with the key and value
    Node<K, V> *newNode = new Node<K, V>(key, value);

    // if index position is empty, add the node
    if (array[index] == NULL) {
      totalQty++;
      array[index] = newNode;
    } else {
      totalQty++;
      // if index position is not empty, add the node to the linked list
      // add to the second position
      Node<K, V> *next = array[index]->next;
      array[index]->next = newNode;
      newNode->next = next;
    }
  }

  // get node
  Node<K, V> *getNode(K key) {
    size_t index = getPossition(key);

    if (index != (size_t)-1) {
      Node<K, V> *current = array[index];

      while (current != NULL) {
        if (current->key == key)
          return current;
        current = current->next;
      }
    }
    return NULL;
  }

  // resize the table
  void resize(size_t newsize) {
    Node<K, V> **oldArray = array;
    size_t old_capacity = capacity;

    array = new Node<K, V> *[newsize];

    for (size_t i = 0; i < newsize; ++i) {
      array[i] = 0;
    }

    capacity = newsize;
    qty = 0;

    for (size_t i = 0; i < old_capacity; ++i) {
      if (oldArray[i] != NULL) {
        put(oldArray[i]->key, oldArray[i]->value);
      }
    }

    delete[] oldArray;
  }

  // override the operator for inserting or getting
  V &operator[](K key) {
    if (!contains(key))
      put(key, V());

    Node<K, V> *node = getNode(key);

    return node->value;
  }


  // get all the keys
  /*
  std::vector<K> getKeys() {

    std::vector<K> thekeys;

    for (size_t i = 0; i < capacity; ++i) {
      if (array[i] != NULL)
        for (Node<K, V> *x = array[i]; x != NULL; x = x->next) {
          thekeys.push_back(x->key);
        }
    }
    return thekeys;
  }
  */

};

#endif

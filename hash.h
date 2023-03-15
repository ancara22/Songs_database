#ifndef _HASH_HPP_
#define _HASH_HPP_

#include <vector>
#include "song.h"
#include <iostream>
#include <cctype>
#include <string>

template <typename K, typename V>
struct Node {
  K key;                  // Artist name
  V value;                // Song object
  Node<K, V> *next;       // next node/song

  Node(K k, V v) {
    this->key = k;
    this->value = v;
    this->next = nullptr;
  }
};

template <typename K, typename V>
class SeparateChaningHash {
private:
  Node<K, V> **array;
  size_t qty;
  size_t capacity;

public:
  SeparateChaningHash() {
    capacity = 97;
    qty = 0;
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
    if (qty >= capacity / 2) {
      resize(2 * capacity); // resize by 2
    }
    
    // hash the key
    size_t index = std::hash<K>{}(key) % capacity;

    // create a new node with the key and value
    Node<K, V> *newNode = new Node<K, V>(key, value);

    // if index position is empty, add the node
    if (array[index] == NULL) {;
      array[index] = newNode;
    } else {

      // if index position is not empty, add the node to the linked list
      // add to the second position
      Node<K, V> *next = array[index]->next;
      array[index]->next = newNode;
      newNode->next = next;

    }
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
        for (Node<K, V> *x = oldArray[i]; x != NULL; x = x->next) {
          put(x->key, x->value);
        }     
      }
    }

    delete[] oldArray;
  }

  //get all nodes with selected key
  std::vector<Node<K, V>*> search(K key) {
    size_t index = getPossition(key);

    std::vector<Node<K, V>*> resultNodes;

    if (index != (size_t)-1) {
      Node<K, V> *current = array[index];

      while (current != NULL) {
        std::string currentKey = current->key;

        toLowerCase(currentKey);
        toLowerCase(key);

        if(currentKey == key) {
          resultNodes.push_back(current);
        }
        current = current->next;
      }
      
    }

    return resultNodes;
  }

  //string to lower case
  void toLowerCase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(),
    [](unsigned char c){ return std::tolower(c); });
  }

  //remove node with combination key and value
  bool remove(K key, K title) {
    size_t index = getPossition(key);

    Node<K, V> *node = array[index],
              *previousNode = NULL;
    
    bool stop = false;

    toLowerCase(title);
    toLowerCase(key);

    while (node != NULL &&  !stop ) {
      std::string songTitle = node->value.getTitle();
      std::string songKey = node->key;

      toLowerCase(songTitle);
      toLowerCase(songKey);
      
      if(songKey == key && songTitle == title) {
        stop = true;
      } else {
        previousNode = node;      
        node = node->next; 
      }
      
    }

    if(node == NULL) {
      return false;
    } else {
      if(previousNode == NULL) {
        array[index] = node->next;
      } else {
        previousNode->next = node->next;
      }
      delete node;
      node = NULL;

      return true;
    }

  }

  //remove all nodes with key
  void remove(K key) {
    size_t index = getPossition(key);

    Node<K, V> *node = array[index],
              *previousNode = NULL;
    
    toLowerCase(key);

    while (node != NULL) {
      std::string songKey = node->key;

      toLowerCase(songKey);
      
      if(songKey == key) {
        if(previousNode == NULL) {
          array[index] = node->next;
          delete node;
          node = array[index];
        } else {
          previousNode->next = node->next;
          delete node;
          node = previousNode->next;
        }

      } else {
        previousNode = node;      
        node = node->next; 
      }
    }

      
      
    

  }

  //get all nodes
  std::vector<Node<K, V>*> getAllNodes() {
    std::vector<Node<K, V>*> nodeKeys;

    for (size_t i = 0; i < capacity; ++i) {
      if (array[i] != NULL)
        for (Node<K, V> *x = array[i]; x != NULL; x = x->next) {
          nodeKeys.push_back(x);
        }
    }
    return nodeKeys;
  }

};


#endif

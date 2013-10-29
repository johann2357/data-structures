#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <utility>
#include <cmath>
#include "AVLTree.h"

template <typename T, typename S>
struct HashFunction
{
  S operator() (T key)
  {
    S result = -1;
    result -= (S)key;
    return std::abs(result);
  }
};

template <typename K, typename V, typename _S>
struct Traits
{
  typedef _S S;
  typedef HashFunction<K,S> HF;
  typedef AVLTree<K,V> DS;
};

template <typename K, typename V, class Tr=Traits<K,V,unsigned int> >
class HashTable
{
  typedef typename Tr::S S;
  typedef typename Tr::HF HF;
  typedef typename Tr::DS DS;
  HF hash_function_;
  DS** array_;
  S size_;
 public:
  HashTable(S size=131): size_(size)
  {
    array_ = new DS* [size_];
    for (S i = 0; i < size_; ++i)
      array_[i] = new DS;
  }
  virtual ~HashTable()
  {
    for (S i = 0; i < size_; ++i) 
      delete array_[i];
    delete[] array_;
  }
  V find(K key)
  {
    return array_[hash_function_(key)%size_]->find(key);
  }
  bool insert(K key, V value)
  {
    return array_[hash_function_(key)%size_]->insert(key, value);
  }
  bool erase(K key)
  {
    return array_[hash_function_(key)%size_]->remove(key);
  }
  void print()
  {
    for(S i = 0; i < size_; ++i)
      array_[i]->print_level_order();
  }
};

#endif // HASHTABLE_H

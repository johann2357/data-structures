#ifndef TRIE_H
#define TRIE_H

#include <stack>
#include <utility>
#include <queue>
#include <iostream>
#include "Traits.h"

template <typename T>
class Node;

template <typename T, class Tr>
class Trie;

template <typename T>
class Node
{
  template <typename X, class Y> friend class Trie;
  typedef Trie< T, TraitsAscendant<T> > trie;
  T data_;
  Node<T>* leaf_[2];
  trie* child_;
 public:
  Node(T x)
  {
    data_ = x;
    leaf_[0] = NULL;
    leaf_[1] = NULL;
    child_ = NULL;
  }
  Node(T x, Node<T>*& l, Node<T>*& r)
  {
    data_ = x;
    leaf_[0] = l;
    leaf_[1] = r;
    child_ = NULL;
  }
  virtual ~Node() {}
};

template <typename _T, class Tr = TraitsAscendant<_T> >
class Trie
{
  typedef typename Tr::T T;
  typedef typename Tr::C C;
  //typedef typename Tr::S S;
  typedef Node<T> node;
  //
  node* root_;
  C compare_;
  //S split_;
  //
public:
  Trie()
  {
    root_ = NULL;
  }
  virtual ~Trie()
  {
    kill_all(root_);
  }
  //
  bool insert(T x)
  {
    node** p;
    if (find(x, p)) 
      return false;
    (*p) = new node(x);
    return true;
  }
  bool remove(T x)
  {
    node** p;
    if (! find(x, p)) 
      return false;
    bool l = (*p)->leaf_[0], r = (*p)->leaf_[1];
    if (l & r)
    {
      node** q = replace(p);
      (*p)->data_ = (*q)->data_;
      p = q;
      l = (*p)->leaf_[0];
      r = (*p)->leaf_[1];
    }
    if ( !(l | r) )
    {
      delete *p;
      (*p) = NULL;
      return true;
    }
    node* t = *p;
    (*p) = (*p)->leaf_[r];
    delete t;
    return true;
  }
  void print_level_order()
  {
    if (!root_) 
      return;
    std::queue<node*> currentLevel, nextLevel;
    currentLevel.push(root_);
    bool end = true;
    while (!currentLevel.empty())
    {
      node* currNode = currentLevel.front();
      currentLevel.pop();
      if (currNode)
      {
        std::cout << currNode->data_ << "  ";
        nextLevel.push(currNode->leaf_[0]);
        nextLevel.push(currNode->leaf_[1]);
        end = false;
      }
      else
      {
        std::cout << "-  ";
        nextLevel.push(NULL);
        nextLevel.push(NULL);
      }
      if (currentLevel.empty())
      {
        std::cout << std::endl;
        if (end) 
          return;
        std::swap(currentLevel, nextLevel);
        end = true;
      }
    }
  }
 private:
  bool find(T x, node**& p)
  {
    p = &root_;
    while (*p)
    {
      if ((*p)->data_ == x) 
        return true;
      p = & (*p)->leaf_[compare_ ((*p)->data_, x)];
    }
    return false;
  }
  node** replace(node** p)
  {
    node** tmp = &(*p)->leaf_[1];
    while ( (*tmp)->leaf_[0] )
      tmp = &(*tmp)->leaf_[0];
    return tmp;
  }
  void kill_all(node* n)
  {
    if (n == NULL)
      return;
    kill_all(n->leaf_[0]);
    kill_all(n->leaf_[1]);
    delete n->child_;
    delete n;
  }
};

#endif // TRIE_H

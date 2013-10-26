#ifndef BINTREE_H
#define BINTREE_H

#include <stack>
#include <utility>
#include <queue>
#include <iostream>
#include "Traits.h"

template <typename T>
class Node
{
  template <typename X, class Y> friend class BinTree;
  template <class X> friend class BinTreeIterator;
  template <class X> friend class Inorder; 
  template <class X> friend class Preorder; 
  template <class X> friend class Postorder;  
  T data_;
  Node<T>* leaf_[2];
public:
  Node(T x)
  {
    data_ = x;
    leaf_[0] = NULL;
    leaf_[1] = NULL;
  }
  Node(T x, Node<T>*& l, Node<T>*& r)
  {
    data_ = x;
    leaf_[0] = l;
    leaf_[1] = r;
  }
  virtual ~Node() {}
};

template <typename _T, class Tr = TraitsAscendant<_T> >
class BinTree
{
  typedef typename Tr::T T;
  typedef typename Tr::C C;
  typedef Node<T> node;
  //
  node* root_;
  C compare_;
  //
public:
  typedef BinTreeIterator< Inorder< Forward<T> > > iterator;
  typedef BinTreeIterator< Inorder< Reverse<T> > > riterator;
  typedef BinTreeIterator< Preorder< Forward<T> > > preorder;
  typedef BinTreeIterator< Preorder< Reverse<T> > > rpreorder;
  typedef BinTreeIterator< Postorder< Forward<T> > > postorder;
  typedef BinTreeIterator< Postorder< Reverse<T> > > rpostorder;
  //
  BinTree()
  {
    root_ = NULL;
  }
  virtual ~BinTree()
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
  iterator begin()
  {
    iterator result;
    result.begin(root_);
    return result;
  }
  iterator end()
  {
    iterator result;
    return result;
  }
  riterator rbegin()
  {
    riterator result;
    result.begin(root_);
    return result;
  }
  riterator rend()
  {
    riterator result;
    return result;
  }
  preorder preorder_begin()
  {
    preorder result;
    result.begin(root_);
    return result;
  }
  preorder preorder_end()
  {
    preorder result;
    return result;
  }
  rpreorder rpreorder_begin()
  {
    rpreorder result;
    result.begin(root_);
    return result;
  }
  rpreorder rpreorder_end()
  {
    rpreorder result;
    return result;
  }
  postorder postorder_begin()
  {
    postorder result;
    result.begin(root_);
    return result;
  }
  postorder postorder_end()
  {
    postorder result;
    return result;
  }
  rpostorder rpostorder_begin()
  {
    rpostorder result;
    result.begin(root_);
    return result;
  }
  rpostorder rpostorder_end()
  {
    rpostorder result;
    return result;
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
    delete n;
  }
};

template <class Tr>
class BinTreeIterator
{
  typedef BinTreeIterator<Tr> self;
  typedef typename Tr::T T;
  typedef typename Tr::node node;
  typedef typename Tr::stack stack;
  typedef typename Tr::I I;
  typedef typename Tr::state state;
  //
  stack stack_;
  I increment_;
  I initialize_;
public:
  BinTreeIterator() {}
  BinTreeIterator(const self& ci)
  {
    stack_ = ci.stack_;
  }
  //
  self& operator= (const self& i)
  {
    stack_ = i.stack_;
    return *this;
  }
  bool operator!= (self i)
  {
    return (stack_.empty() != i.stack_.empty());
  }
  bool operator== (self i)
  {
    if (stack_.empty() == i.stack_.empty())
      return true;
    return (stack_.top().second == i.stack_.top().second);
  }
  T operator* ()
  {
    return stack_.top().second->data_;
  }
  self& operator++ ()
  {
    state s;
    do
    {
      s = increment_(stack_);
      if (s == Tr::U_)
        stack_.pop();
    } while ( (s != Tr::S_) && (!stack_.empty()) );
    return *this;
  }
  self operator++ (int)
  {
    self tmp(*this);
    ++(*this);
    return tmp;
  }
  friend std::ostream& operator<<(std::ostream& out, const self& x)
  {
    std::cout << x.stack_.top().second;
  }
  self begin(node* r)
  {
    initialize_(stack_, r);
    return *this;
  }
};

#endif // BINTREE_H

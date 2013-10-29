#ifndef AVLTREE_H
#define AVLTREE_H

#include <stack>
#include <queue>
#include <utility>
#include <stdlib.h>
#include "Traits.h"

template <typename T, typename V>
class Node
{
  template <typename X, typename Y, class Z> friend class AVLTree;                             
  T data_;
  V value_;
  int height_;
  Node<T,V>* leaf_[2];
public:
  Node(T x, V y)
  {
    data_ = x;
    value_ = y;
    leaf_[0] = NULL;
    leaf_[1] = NULL;
    height_ = 0;
  }
  virtual ~Node() {}
};

template <typename _T, typename _V, class Tr = TraitsAscendant<_T> >
class AVLTree
{
  typedef _V V;
  typedef typename Tr::T T;
  typedef typename Tr::C C;
  typedef Node<T,V> node;
  typedef std::stack<node**> stack;
  //
  node* root_;
  C compare_;
  //
public:
  AVLTree()
  {
    root_ = NULL;
  }
  virtual ~AVLTree()
  {
    kill_all(root_);
  }
  //
  bool insert(T x, V y)
  {
    node** p;
    stack path;
    if (find(x, p, path))
    {
      (*p)->value_ = y;
      return true;
    }
    (*p) = new node(x, y);
    update_balance_path(path);
    return true;
  }
  V find(T x)
  {
    node** p = &root_;
    while (*p)
    {
      if ((*p)->data_ == x)
        return (*p)->value_;
      p = & (*p)->leaf_[compare_ ((*p)->data_, x)];
    }
    return V();
  }
  bool remove(T x)
  {
    node** p;
    stack path;
    if (! find(x, p, path)) 
      return false;
    bool l = (*p)->leaf_[0], r = (*p)->leaf_[1];
    if (l & r)
    {
      node** q = replace(p, path);
      (*p)->data_ = (*q)->data_;
      (*p)->value_ = (*q)->value_;
      p = q;
      l = (*p)->leaf_[0];
      r = (*p)->leaf_[1];
    }
    if ( !(l | r) )
    {
      delete *p;
      (*p) = NULL;
      update_balance_path(path);
      return true;
    }
    node* t = *p;
    (*p) = (*p)->leaf_[r];
    delete t;
    update_balance_path(path);
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
  bool find(T x, node**& p, stack& path)
  {
    p = &root_;
    while (*p )
    {
      if ((*p)->data_ == x) 
        return true;
      path.push( p );
      p = & (*p)->leaf_[compare_ ((*p)->data_, x)];
    }
    return false;
  }
  node** replace(node** p, stack path)
  {
    path.push(p);
    node** tmp = &(*p)->leaf_[1];
    while ( (*tmp)->leaf_[0] )
    {
      path.push(tmp);
      tmp = &(*tmp)->leaf_[0];
    }
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
  int height(node* ptr)
  {
    if (ptr)
      return ptr->height_;
    return -1;
  }
  void update_height(node*& ptr)
  {
    if (ptr)
      ptr->height_ = std::max( height(ptr->leaf_[0]), height(ptr->leaf_[1]) ) + 1;
  }
  void rotate(node** ptr, bool dir)
  {
    node* tmp = (*ptr);
    (*ptr) = (*ptr)->leaf_[dir];
    tmp->leaf_[dir] = (*ptr)->leaf_[!dir];
    (*ptr)->leaf_[!dir] = tmp;
  }
  void rotate2(node** ptr, bool dir)
  {
    rotate( &(*ptr)->leaf_[dir], !dir ); 
    rotate( ptr, dir );
  }
  void balance(node** ptr)
  {
    if ( !(*ptr)->leaf_[0] && !(*ptr)->leaf_[1] ) 
      return;
    int factor = height( (*ptr)->leaf_[0] ) - height( (*ptr)->leaf_[1] ); 
    if (factor == 2)
    {
      bool double_rotation = height( (*ptr)->leaf_[0]->leaf_[0]) <
                             height( (*ptr)->leaf_[0]->leaf_[1]) ;
      if (double_rotation)
        rotate2(ptr, 0);
      else
        rotate(ptr, 0);
    }
    else if (factor == -2)
    {
      bool double_rotation = height( (*ptr)->leaf_[1]->leaf_[0]) >
                             height( (*ptr)->leaf_[1]->leaf_[1]) ;
      if (double_rotation)
        rotate2(ptr, 1);
      else
        rotate(ptr, 1);
    } 
    else
      return;
    update_height( (*ptr)->leaf_[0] );
    update_height( (*ptr)->leaf_[1] );

  }
  void update_balance_path(stack& path)
  {
    while ( !path.empty() )
    {
      balance( path.top() );
      update_height( *path.top() );
      path.pop();
    }
  }
};

#endif // AVLTREE_H

#ifndef AVLTREE_H
#define AVLTREE_H

#include <stack>
#include <queue>
#include <utility>
#include <stdlib.h>
#include "Traits.h"

template <typename T>
class Node
{
  template <typename X, class Y> friend class AVLTree;                             
  template <class X> friend class AVLTreeIterator; 
  template <class X> friend class Inorder; 
  template <class X> friend class Preorder; 
  template <class X> friend class Postorder; 
  T data_;
  int height_;
  Node<T>* leaf_[2];
public:
  Node(T x)
  {
    data_ = x;
    leaf_[0] = NULL;
    leaf_[1] = NULL;
    height_ = 0;
  }
  Node(T x, int h)
  {
    data_ = x;
    leaf_[0] = NULL;
    leaf_[1] = NULL;
    height_ = h;
  }
  virtual ~Node() {}
};

template <typename _T, class Tr = TraitsAscendant<_T> >
class AVLTree
{
  typedef typename Tr::T T;
  typedef typename Tr::C C;
  typedef Node<T> node;
  typedef std::stack<node**> stack;
  //
  node* root_;
  C compare_;
  //
public:
  typedef AVLTreeIterator< Inorder< Forward<T> > > iterator;
  typedef AVLTreeIterator< Inorder< Reverse<T> > > riterator;
  typedef AVLTreeIterator< Preorder< Forward<T> > > preorder;
  typedef AVLTreeIterator< Preorder< Reverse<T> > > rpreorder;
  typedef AVLTreeIterator< Postorder< Forward<T> > > postorder;
  typedef AVLTreeIterator< Postorder< Reverse<T> > > rpostorder;
  //
  AVLTree()
  {
    root_ = NULL;
  }
  virtual ~AVLTree()
  {
    kill_all(root_);
  }
  //
  bool insert(T x)
  {
    node** p;
    stack path;
    if (find(x, p, path)) 
      return false;
    (*p) = new node(x);
    update_balance_path(path);
    return true;
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

template <class Tr>
class AVLTreeIterator
{
  typedef AVLTreeIterator<Tr> self;
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
  AVLTreeIterator() {}
  AVLTreeIterator(const self& ci)
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

#endif // AVLTREE_H

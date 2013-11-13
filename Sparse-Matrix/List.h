#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class LNode
{
 public:
  T data_;
  int coord_[2];
  LNode<T>* next_[2];
  LNode(T d)
  {
    data_ = d;
    next_[0] = NULL;
    next_[1] = NULL;
  }
  virtual ~LNode() {}
};

template <typename T>
class ListIterator;

template <typename T>
class List
{
  typedef List<T> self;
  typedef LNode<T> node;
  bool dir_;
  unsigned int size_;
 public:
  node* head_;
  typedef ListIterator<T> iterator;
  List(bool d=true): dir_(d)
  {
    head_ = NULL;
    size_ = 0;
  }
  virtual ~List()
  {
    node* t;
    while (head_)
    {
      t = head_->next_[dir_];
      delete head_;
      head_ = t;
    }
  }
  node** find(int c) 
  {
    node** p = NULL;
    p = &head_;
    while ( *p && ((*p)->cood_[dir_] < c))
      p = &(*p)->next_[dir_];
    return p;
  }
  bool insert(T x, int current, int other_coord, self* other)
  {
    node** cp = find(other_coord);
    if ( ((*cp) != NULL) && ((*cp)->coord_[dir_] == other_coord) )
    {
      (*cp)->data = x;
      return false;
    }
    node** op = other->find(current);
    node* tmp = (*cp);
    (*cp) = new node (x);
    (*cp)->next_[dir_] = tmp;
    tmp = (*op);
    (*cp)->next_[!dir_] = tmp;
    ++size_;
    return true;
  }
  bool remove(int current, int other_coord, self* other)
  {
    node** cp = find(other_coord);
    if ( ((*cp) != NULL) && ((*cp)->coord_[dir_] != other_coord) )
      return false;
    node** op = other->find(current);
    node* tmp = (*cp);
    (*cp) = (*cp)->next_[dir_];
    (*op) = (*op)->next_[!dir_];
    delete tmp;
    --size_;
    return true;
  }
  unsigned int size()
  {
    return size_;
  }
  iterator begin()
  {
    iterator tmp(head_);
    return tmp;
  }
  iterator end()
  {
    return NULL;
  }
};

template <typename T>
class ListIterator
{
  typedef ListIterator<T> self;
  typedef LNode<T> node;
  node* i_;
public:
  ListIterator(node* p=NULL)
  {
    i_ =  p;
  }
  ListIterator(const self& ci)
  {
    i_ = ci.i_;
  }
  self& operator= (const self& i)
  {
    i_ = i.i_;
    return *this;
  }
  bool operator!= (self i)
  {
    return (i_ != i.i_);
  }
  bool operator== (self i)
  {
    return (i_ == i.i_);
  }
  T operator* ()
  {
    return i_->data_;
  }
  self& operator++ ()
  {
    i_ = i_->next_;
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
    std::cout << x.i_;
  }
};

#endif // LIST_H

#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class LNode;

template <typename T>
class List;

template <typename T>
class ListIterator;

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
class List
{
  typedef List<T> self;
  typedef LNode<T> node;
 public:
  bool dir_;
  unsigned int size_;
  node* head_;
  typedef ListIterator<T> iterator;
  List(bool d=true): dir_(d)
  {
    head_ = NULL;
    size_ = 0;
  }
  virtual ~List()
  {
    if (dir_)
    {
      node* t;
      while (head_)
      {
        t = head_->next_[dir_];
        delete head_;
        head_ = t;
      }
    }
    else
      head_ = NULL;
  }
  bool find(int c, node**& p) 
  {
    p = &head_;
    while ( (*p) && ((*p)->coord_[dir_] < c))
      p = &(*p)->next_[dir_];
    return ((*p != NULL) && ((*p)->coord_[dir_] == c));
  }
  bool insert(T x, int other_coord, int current, self* other)
  {
    node** cp;
    if (find(other_coord, cp))
    {
      (*cp)->data_ = x;
      return false;
    }
    node** op;
    other->find(current, op);
    node* tmp = (*cp);
    (*cp) = new node (x);
    (*cp)->coord_[!dir_] = current;
    (*cp)->coord_[dir_] = other_coord;
    (*cp)->next_[dir_] = tmp;
    tmp = (*op);
    (*cp)->next_[!dir_] = tmp;
    (*op) = (*cp);
    ++(*this);
    ++(*other);
    return true;
  }
  bool remove(int other_coord, int current, self* other)
  {
    node** cp;
    if (!find(other_coord, cp))
      return false;
    node** op;
    other->find(current, op);
    node* tmp = (*cp);
    (*cp) = (*cp)->next_[dir_];
    (*op) = (*op)->next_[!dir_];
    delete tmp;
    --(*this);
    --(*other);
    return true;
  }
  unsigned int size()
  {
    return size_;
  }
  void operator++()
  {
    ++size_;
  }
  void operator--()
  {
    --size_;
  }
  iterator begin()
  {
    iterator tmp(head_, dir_);
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
  int ldir_;
  node* i_;
public:
  ListIterator(node* p=NULL, int dir=0)
  {
    i_ =  p;
    ldir_ = dir;
  }
  ListIterator(const self& ci)
  {
    i_ = ci.i_;
  }
  self& operator= (const self& i)
  {
    i_ = i.i_;
    ldir_ = i.ldir_;
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
    i_ = i_->next_[ldir_];
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
    std::cout << "\tdata: " << x.i_->data_;
    std::cout << "\ncoord 0: " << x.i_->coord_[0];
    std::cout << "\ncoord 1: " << x.i_->coord_[1];
    std::cout << "\n";
  }
};

#endif // LIST_H

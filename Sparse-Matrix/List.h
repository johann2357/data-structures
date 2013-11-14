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
struct SMNode;

template <typename T>
struct SMNode
{
  typedef List<T> list;
  typedef LNode<T> node;
  typedef SMNode<T> self;
  list* list1_;
  list* list2_;
  T zero_;
  int coord1_;
  int coord2_;
  SMNode(list* pl1, list* pl2, int coord1, int coord2, T zero)
  {
    list1_ = pl1;
    list2_ = pl2;
    zero_ = zero;
    coord1_ = coord1;
    coord2_ = coord2;
  }
  virtual ~SMNode() {}
  operator T ()
  {
    node** tmp;
    if (list1_->find(coord1_, tmp))
      return (*tmp)->data_;
    return zero_;
  }
  self& operator= (const T& x)
  {
    if (x == zero_)
      list1_->remove(coord1_, coord2_, list2_);
    else
      list1_->insert(x, coord1_, coord2_, list2_);
    return (*this);
  }
};

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
    node* t;
    while (head_)
    {
      t = head_->next_[dir_];
      delete head_;
      head_ = t;
    }
  }
  bool find(int c, node**& p) 
  {
    p = &head_;
    while ( (*p) && ((*p)->coord_[dir_] < c))
      p = &(*p)->next_[dir_];
    return ((*p != NULL) && ((*p)->coord_[dir_] == c));
  }
  bool insert(T x, int current, int other_coord, self* other)
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
    (*cp)->coord_[dir_] = current;
    (*cp)->coord_[!dir_] = other_coord;
    (*cp)->next_[dir_] = tmp;
    tmp = (*op);
    (*cp)->next_[!dir_] = tmp;
    ++size_;
    return true;
  }
  bool remove(int current, int other_coord, self* other)
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

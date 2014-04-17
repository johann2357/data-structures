#ifndef BTREE
#define BTREE

#include <utility>

template <typename T>
struct Page
{
  int number_;
  T* data_;
  Page<T>* sons_;
  Page(int n)
  {
    number_ = 0;
    sons_ = new Page<T> [n];
  }
  virtual ~Page()
  {
    if (sons_)
      delete[] sons_;
    if (data)
      delete[] data_;
  }
  bool leaf()
  {
    return (sons_ == NULL);
  }
};

template <typename T>
struct BTree
{
  typedef Page<T> page;
  typedef std::pair<page*, int> pair;
  pair search(page* x, T k)
  {
    int i = 0;
    while ((i <= x->number_) && (k > x->data_[i]))
      ++i;
    if ((i <= x->number_) && (k == x->data_[i]))
      return std::make_pair(x, i);
    else if (x->leaf())
      return NULL;
    else
      return search(x-sons_[i], k);
  }
};



#endif

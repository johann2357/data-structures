#include "List.h"
#include <stdexcept>

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

template <typename T, T zero>
class SparseMatrix
{
  typedef List<T> list;
  typedef SMNode<T> smnode;
 public:
  list** above_;
  list** left_;
  int rows_;
  int columns_;
  SparseMatrix(int r=0, int c=0): rows_(r), columns_(c)
  {
    if (r && c)
    {
      above_ = new list* [columns_];
      for (int i = 0; i < columns_; ++i)
        above_[i] = new list(0);
      left_ = new list* [rows_];
      for (int i = 0; i < rows_; ++i)
        left_[i] = new list(1);
    }
  }
  virtual ~SparseMatrix()
  {
    if (above_ && left_)
    {
      for (int i = 0; i < columns_; ++i)
        delete above_[i];
      for (int i = 0; i < rows_; ++i)
        delete left_[i];
      delete[] above_;
      delete[] left_;
    }
  }
  smnode operator() (int x, int y)
  {
    if ((x > rows_) || (y > columns_))
      throw std::out_of_range("not such position");
    list* tmp[2];
    bool dir = left_[x]->size() < above_[y]->size();
    tmp[!dir] = left_[x];
    tmp[dir] = above_[y];
    if (!dir)
      std::swap(x, y);
    return smnode(tmp[0], tmp[1], y, x, zero);
  }
};

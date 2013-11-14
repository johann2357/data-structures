#include "List.h"
#include <stdexcept>

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
    tmp[dir] = left_[x];
    tmp[!dir] = above_[y];
    if (false && dir)
      std::swap(x, y);
    return smnode(left_[x], above_[y], y, x, zero);
    return smnode(tmp[0], tmp[1], x, y, zero);
  }
};

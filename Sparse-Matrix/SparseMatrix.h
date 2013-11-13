#include "List.h"

template <typename T, T zero>
class SparseMatrix
{
  typedef List<T> list;
 public:
  list* above_;
  list* left_;
  int rows_;
  int columns_;
  SparseMatrix(int r=0, int c=0): rows_(r), columns_(c)
  {
    if (r && c)
    {
      above_ = new list [columns_];
      left_ = new list [rows_];
    }
  }
  virtual ~SparseMatrix()
  {
    if (above_ && left_)
    {
      delete[] above_;
      delete[] left_;
    }
  }
};

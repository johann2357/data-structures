#ifndef SMART_ARRAY
#define SMART_ARRAY

template <typename T>
class SmartArray
{
  typedef SmartArray<T> self;
  T* data_;
 public:
  SmartArray()
  {
    data_ = NULL;
  }
  SmartArray(T* ptr)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete[] data_;
      GCTable[data_] -= 1;
    }
    data_ = ptr;
    if (ptr)
      GCTable[data_] += 1;
  }
  SmartArray(const self& sa)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete[] data_;
      GCTable[data_] -= 1;
    }
    data_ = sa.data_;
    if (data_)
      GCTable[data_] += 1;
  }
  virtual ~SmartArray()
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete[] data_;
      GCTable[data_] -= 1;
    }
  }
  self& operator = (T* ptr)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete[] data_;
      GCTable[data_] -= 1;
    }
    data_ = ptr;
    if (ptr)
      GCTable[data_] += 1;
    return (*this);
  }
  self& operator = (const self& sp)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete[] data_;
      GCTable[data_] -= 1;
    }
    data_ = sp.data_;
    if (data_)
      GCTable[data_] += 1;
    return (*this);
  }
  Element<T> operator * ()
  {
    return Element<T> (data_);
  }
  operator T* ()
  {
    return data_;
  }
  Element<T> operator [] (int pos)
  {
    return Element<T> (data_ + pos);
  }
  friend std::ostream& operator<<(std::ostream& out, const self& x)
  {
    std::cout << x.data_;
  }
};

#endif

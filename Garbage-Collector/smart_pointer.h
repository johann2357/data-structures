#ifndef SMART_PTR
#define SMART_PTR

template <typename T>
class SmartPtr
{
  typedef SmartPtr<T> self;
  T* data_;
 public:
  SmartPtr()
  {
    data_ = NULL;
  }
  SmartPtr(T* ptr)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete data_;
      GCTable[data_] -= 1;
    }
    data_ = ptr;
    if (ptr)
      GCTable[data_] += 1;
  }
  SmartPtr(const self& sp)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete data_;
      GCTable[data_] -= 1;
    }
    data_ = sp.data_;
    if (data_)
      GCTable[data_] += 1;
  }
  virtual ~SmartPtr()
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete data_;
      GCTable[data_] -= 1;
    }
  }
  self& operator = (T* ptr)
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete data_;
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
        delete data_;
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
  friend std::ostream& operator<<(std::ostream& out, const self& x)
  {
    std::cout << x.data_;
  }
};

#endif

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
    data_ = ptr;
    increment();
  }
  SmartPtr(const self& sp)
  {
    data_ = sp.data_;
    increment();
  }
  virtual ~SmartPtr()
  {
    decrement();
  }
  self& operator = (T* ptr)
  {
    decrement();
    data_ = ptr;
    increment();
    return (*this);
  }
  self& operator = (const self& sp)
  {
    decrement();
    data_ = sp.data_;
    increment();
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
 private:
  void increment()
  {
    if (data_)
      ++GCTable[data_];
  }
  void decrement()
  {
    if (data_)
    {
      if (GCTable[data_] == 1)
        delete data_;
      --GCTable[data_];
    }
  }
};

#endif

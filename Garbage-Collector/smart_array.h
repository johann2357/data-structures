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
    data_ = ptr;
    increment();
  }
  SmartArray(const self& sa)
  {
    data_ = sa.data_;
    increment();
  }
  virtual ~SmartArray()
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
  Element<T> operator [] (int pos)
  {
    return Element<T> (data_ + pos);
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
        delete[] data_;
      --GCTable[data_];
    }
  }
};

#endif

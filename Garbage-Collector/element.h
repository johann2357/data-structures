#ifndef ELEMENT
#define ELEMENT

template <typename T>
class Element
{
  typedef Element<T> self;
  T* data_;
 public:
  Element(T* ptr)
  {
    data_ = ptr;
  }
  void operator = (T d)
  {
    (*data_) = d;
  }
  operator T ()
  {
    return (*data_);
  }
  friend std::ostream& operator<<(std::ostream& out, const self& x)
  {
    std::cout << *(x.data_);
  }
};

#endif

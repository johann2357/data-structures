#include <cstring>
#include <iostream>

class BitVector
{
  unsigned char* data_;
  int size_;
 public:
  BitVector(int bits) 
  {
    size_ =  bits / 8;
    if (bits % 8)
      ++size_;
    data_ = new unsigned char [size_];
    std::memset(data_, sizeof(unsigned char)*size_, 0);
  }
  virtual ~BitVector()
  {
    delete[] data_;
  }
  void set_bit(int pos, bool value)
  {
    int apos = pos / 8;
    int bitp = pos % 8;
    unsigned char r = 1;
    r <<= bitp;
    if (value)
      data_[apos] |= r;
    else
      data_[apos] &= (~r);
  }
  bool get_bit(int pos)
  {
    int apos = pos / 8;
    int bitp = pos % 8;
    return (( data_[apos] >> bitp ) & 1);
  }
  void print()
  {
    for (int i = size_*8-1; i >= 0; --i)
      std::cout << get_bit(i);
    std::cout << std::endl;
  }       
};


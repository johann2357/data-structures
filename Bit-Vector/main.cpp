#include "bitvector.h"

int main()
{
  BitVector test(22);
  test.set_bit(3, true);
  test.set_bit(8, true);
  test.set_bit(14, true);
  test.set_bit(3, false);
  test.set_bit(1, true);
  std::cout << test.get_bit(9) << std::endl;
  test.print();
  return 0;
}


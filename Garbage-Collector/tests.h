#include "garbage_collector.h"
#include "debug.h"

struct UnitTest
{
  void test_pointer()
  {
    SmartPtr<int> test = NULL;
    test = new int(6);
    (*test) = 66;
    Debug((*test) << '\n');
  }
  void test_array()
  {
    SmartArray<int> test = NULL;
    test = new int [6];
    test[0] = 66;
    test[4] = 6;
    Debug(test[0] << '\n');
    Debug(test[4] << '\n');
  }
  void run()
  {
    test_pointer();
    test_array();
  }
};

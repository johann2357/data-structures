#include "garbage_collector.h"
#include "debug.h"
#include <assert.h>

struct UnitTest
{
  void status()
  {
    Debug("contains: ");
    for (auto& a: GCTable)
      Debug("  " << a.first << " : " << a.second);
    Debug("\n");
  }
  void test_pointer()
  {
    Debug("test_pointer\n");
    SmartPtr<int> test = new int(6);
    (*test) = 66;
    assert((*test) == 66);
    /**/ status(); /**/
    SmartPtr<int> copy = test;
    assert((*copy) == 66);
    /**/ status(); /**/ 
  }
  void test_array()
  {
    Debug("test_array\n");
    SmartArray<int> test = NULL;
    test = new int [6];
    test[1] = 66;
    test[4] = 6;
    assert(test[1] == 66);
    assert(test[4] == 6);
    /**/ status(); /**/
    SmartArray<int> copy = test;
    /**/ status(); /**/
    test = new int [3];
    test[1] = 666;
    assert(test[1] == 666);
    assert(copy[1] == 66);
    /**/ status(); /**/
  }
  void run()
  {
    /**/ status(); /**/ 
    test_pointer();
    /**/ status(); /**/ 
    test_array();
    /**/ status(); /**/ 
  }
};

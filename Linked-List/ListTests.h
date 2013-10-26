#ifndef LISTTESTS_H
#define LISTTESTS_H

#include <assert.h>
#include "debug.h"
#include "List.h"

class ListUnitTest
{
public:
  void test()
  {
    List<int> test;
    test.insert(30);
    test.insert(900);
    test.insert(700);
    test.insert(500);
    test.insert(1);
    for (List<int>::iterator it = test.begin();  it != test.end(); ++it)
      Debug(*it);
    test.remove(1);
    test.remove(900);
    test.remove(500);
    test.remove(700);
    test.remove(30);
    assert(test.begin() == test.end());
  }
  void run()
  {
    test();
  }
};

#endif // LISTTESTS_H

#ifndef TRIETESTS_H
#define TRIETESTS_H

#include <assert.h>
#include "debug.h"
#include "Trie.h"

struct UnitTest
{
  void test_insertion()
  {
    Trie<int> test;
    assert(test.insert(234) == true);
    assert(test.insert(2324) == true);
    assert(test.insert(2) == true);
    assert(test.insert(23400) == true);
    assert(test.insert(23400) == false);
    assert(test.remove(234) == true);
    assert(test.remove(2324) == true);
    assert(test.remove(2) == true);
    assert(test.remove(99) == false);
  }
  void test_print()
  {
    Trie<char> test;
    test.insert('F');
    test.insert('B');
    test.insert('G');
    test.insert('I');
    test.insert('H');
    test.insert('A');
    test.insert('D');
    test.insert('C');
    test.insert('E');
    test.print_level_order();
  }
  void run()
  {
    test_insertion();
    test_print();
  }
};

#endif // TRIETESTS_H

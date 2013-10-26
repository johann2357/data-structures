#ifndef BINTREETESTS_H
#define BINTREETESTS_H

#include <assert.h>
#include "debug.h"
#include "BinTree.h"

struct BinTreeUnitTest
{
  void test_insertion()
  {
    BinTree<int> test;
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
    BinTree<char> test;
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
  void test_inorder()
  {
    BinTree<char> test;
    test.insert('F');
    test.insert('B');
    test.insert('G');
    test.insert('I');
    test.insert('H');
    test.insert('A');
    test.insert('D');
    test.insert('C');
    test.insert('E');
    Debug("inorder");
    BinTree<char>::iterator it;
    for (it = test.begin(); it != test.end(); ++it)
      Debug(*it);
    Debug("reverse inorder");
    BinTree<char>::riterator ri;
    for (ri = test.rbegin(); ri != test.rend(); ++ri)
      Debug(*ri);
  }
  void test_preorder()
  {
    BinTree<char> test;
    test.insert('F');
    test.insert('B');
    test.insert('G');
    test.insert('I');
    test.insert('H');
    test.insert('A');
    test.insert('D');
    test.insert('C');
    test.insert('E');
    Debug("preorder");
    BinTree<char>::preorder pi;
    for (pi = test.preorder_begin(); pi != test.preorder_end(); ++pi)
      Debug(*pi);
    Debug("reverse preorder");
    BinTree<char>::rpreorder rpi;
    for (rpi = test.rpreorder_begin(); rpi != test.rpreorder_end(); ++rpi)
      Debug(*rpi);
  }
  void test_postorder()
  {
    BinTree<char> test;
    test.insert('F');
    test.insert('B');
    test.insert('G');
    test.insert('I');
    test.insert('H');
    test.insert('A');
    test.insert('D');
    test.insert('C');
    test.insert('E');
    Debug("postorder");
    BinTree<char>::postorder posti;
    for (posti = test.postorder_begin(); posti != test.postorder_end(); ++posti)
      Debug(*posti);
    Debug("reverse postorder");
    BinTree<char>::rpostorder rposti;
    for (rposti = test.rpostorder_begin(); rposti != test.rpostorder_end(); ++rposti)
      Debug(*rposti);
  }
  void run()
  {
    test_insertion();
    test_print();
    test_inorder();
    test_preorder();
    test_postorder();
  }
};

#endif // BINTREETESTS_H

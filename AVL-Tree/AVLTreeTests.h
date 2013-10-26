#ifndef AVLTREETESTS_H
#define AVLTREETESTS_H

#include <assert.h>
#include "debug.h"
#include "AVLTree.h"

struct AVLTreeUnitTest
{
  void test_simple_balance()
  {
    AVLTree<int> test;
    assert(test.insert(23) == true);
    assert(test.insert(25) == true);
    assert(test.insert(27) == true);
    test.print_level_order();
  }
  void test_double_balance()
  {
    AVLTree<int> test;
    assert(test.insert(23) == true);
    assert(test.insert(25) == true);
    assert(test.insert(24) == true);
    test.print_level_order();
  }
  void test_print()
  {
    AVLTree<char> test;
    test.insert('F');
    test.insert('B');
    test.insert('H');
    test.insert('G');
    test.insert('I');
    test.insert('A');
    test.insert('D');
    test.insert('C');
    test.insert('E');
    test.print_level_order();
  }
  void test_inorder()
  {
    AVLTree<char> test;
    test.insert('F');
    test.insert('B');
    test.insert('H');
    test.insert('G');
    test.insert('I');
    test.insert('A');
    test.insert('D');
    test.insert('C');
    test.insert('E');
    Debug("inorder");
    AVLTree<char>::iterator it;
    for (it = test.begin(); it != test.end(); ++it)
      Debug(*it);
    Debug("reverse inorder");
    AVLTree<char>::riterator ri;
    for (ri = test.rbegin(); ri != test.rend(); ++ri)
      Debug(*ri);
  }
  void test_preorder()
  {
    AVLTree<char> test;
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
    AVLTree<char>::preorder pi;
    for (pi = test.preorder_begin(); pi != test.preorder_end(); ++pi)
      Debug(*pi);
    Debug("reverse preorder");
    AVLTree<char>::rpreorder rpi;
    for (rpi = test.rpreorder_begin(); rpi != test.rpreorder_end(); ++rpi)
      Debug(*rpi);
  }
  void test_postorder()
  {
    AVLTree<char> test;
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
    AVLTree<char>::postorder posti;
    for (posti = test.postorder_begin(); posti != test.postorder_end(); 
        ++posti)
      Debug(*posti);
    Debug("reverse postorder");
    AVLTree<char>::rpostorder rposti;
    for (rposti = test.rpostorder_begin(); rposti != test.rpostorder_end(); 
        ++rposti)
      Debug(*rposti);
  }
  void run()
  {
    test_simple_balance();
    test_simple_balance();
    test_print();
    test_inorder();
    test_preorder();
    test_postorder();
  }
};

#endif // AVLTREETESTS_H

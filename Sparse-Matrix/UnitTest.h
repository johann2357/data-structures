#include "SparseMatrix.h"
#include "debug.h"

struct UnitTest
{
  void horizontal_insertion()
  {
    Debug("horizontal_insertion\n");
    SparseMatrix<int, 0> test(7,5);
    test(1,3) = 4;
    test(1,1) = 2;
    test(1,4) = 5;
    test(1,2) = 3;
    test(1,0) = 1;
    int x = test(1,3);
    Debug(x);
    Debug("\n");
  }
  void vertical_insertion()
  {
    Debug("vertical_insertion\n");
    SparseMatrix<int, 0> test(5,7);
    test(3,1) = 4;
    test(1,1) = 2;
    test(4,1) = 5;
    test(2,1) = 3;
    test(0,1) = 1;
    int x = test(3,1);
    Debug(x);
    Debug("\n");
  }
  void insertion()
  {
    Debug("insertion\n");
    SparseMatrix<int, 0> test(5,7);
    test(3,1) = 4;
    test(1,1) = 2;
    test(4,1) = 5;
    test(2,1) = 3;
    test(0,1) = 1;
    test(1,3) = 4;
    test(1,1) = 2;
    test(1,4) = 5;
    test(1,2) = 3;
    test(1,0) = 1;
    int x = test(1,1);
    Debug(x);
    Debug("\n");
  }
  void removal()
  {
    Debug("removal\n");
    SparseMatrix<int, 0> test(5,5);
    test(2,2) = 9;
    test(3,1) = 4;
    test(1,1) = 2;
    test(3,1) = 0;
    test(1,1) = 3;
    test(1,1) = 0;
    int x = test(1,1), y = test(3,1);
    Debug(x << "\n" << y);
    Debug("\n");
  }
  void run()
  {
    horizontal_insertion();
    vertical_insertion();
    insertion();
    removal();
  }
};

#include "SparseMatrix.h"
#include "debug.h"

int main(int argc, char const *argv[]) 
{
  SparseMatrix<int, 0> test(7,5);
  test(1,1) = 4;
  int s = test(1,1);
  Debug(s);
  test(2,3) = 2;
  s = test(2,3);
  Debug(s);
  test(2,1) = 0;
  s = test(2,1);
  Debug(s);
  Debug("\nthe end\n");
  return 0;
}

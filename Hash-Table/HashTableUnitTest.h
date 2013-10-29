#ifndef HASHTABLETESTS_H                                                          
#define HASHTABLETESTS_H                                                          
                                                                                
#include <assert.h>
#include <string>
#include "debug.h"                                                              
#include "HashTable.h"                                                            
                                                                                
struct UnitTest                                                          
{     
  void insertion()
  {
    Debug("test insertion");
    HashTable<int, std::string> test(3);
    test.insert(0,"first");
    test.insert(1,"second");
    test.insert(2,"third");
    test.insert(3,"fourth");
    test.insert(4,"fifth");
    test.insert(5,"sixth");
    test.insert(-1,"last");
    test.print();
  }
  void change_at_insertion()
  {
    Debug("test change at insertion");
    HashTable<int, std::string> test(3);
    test.insert(0,"first");
    assert(test.find(0)=="first");
    test.insert(0,"last");
    assert(test.find(0)=="last");
  }
  void removal()
  {
    Debug("test removal");
    HashTable<int, std::string> test(3);
    test.insert(0,"first");
    test.insert(1,"second");
    test.insert(2,"third");
    test.insert(3,"fourth");
    test.insert(4,"fifth");
    test.insert(5,"sixth");
    test.insert(-1,"last");
    for(int i = 0; i < 6; ++i)
      assert(test.erase(i)==true);
    assert(test.erase(6)==false);
    test.print();
  }
  void run()
  {
    insertion();    
    change_at_insertion();
    removal();
  }                                                                             
};                                                                              
                                                                                
#endif // HASHTABLETESTS_H 

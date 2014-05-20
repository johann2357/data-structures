#ifndef GRAPHTESTS_H
#define GRAPHTESTS_H

#include <assert.h>
#include "debug.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "Traversal.h"

struct GraphUnitTest
{
  void test_insertion()
  {
    Graph<char, int> test;
    assert(test.insert_node('J')==true);
    assert(test.insert_node('A')==true);
    assert(test.insert_node('N')==true);
    assert(test.insert_node('G')==true);
    //
    Graph<char, int>::node *ptr1, *ptr2;
    ptr1 = test.find('N');
    ptr2 = test.find('A');
    test.insert_edge(31, ptr1, ptr2);
    //
    ptr1 = test.find('J');
    ptr2 = test.find('G');
    assert(test.insert_edge(13, ptr1, ptr2)==true);
    test.print();
  }
  void test_edge_removal()
  {
    Graph<char, int> test;
    assert(test.insert_node('J')==true);
    assert(test.insert_node('A')==true);
    assert(test.insert_node('N')==true);
    assert(test.insert_node('G')==true);
    //
    Graph<char, int>::node *ptr1, *ptr2;
    ptr1 = test.find('N');
    ptr2 = test.find('A');
    assert(test.insert_edge(31, ptr1, ptr2)==true);
    //
    ptr1 = test.find('J');
    ptr2 = test.find('G');
    assert(test.insert_edge(13, ptr1, ptr2)==true);
    //
    ptr1 = test.find('A');
    ptr2 = test.find('G');
    assert(test.insert_edge(100, ptr1, ptr2)==true);
    //
    Debug("\t**Before**");
    test.print();
    Graph<char, int>::eiterator eit = (*ptr1).begin();
    test.remove_edge((*eit).first);
    Debug("\t**After**");
    test.print();
  }
  void test_node_removal()
  {
    Graph<char, int> test;
    assert(test.insert_node('J')==true);
    assert(test.insert_node('A')==true);
    assert(test.insert_node('N')==true);
    assert(test.insert_node('G')==true);
    //
    Graph<char, int>::node *ptr1, *ptr2;
    ptr1 = test.find('N');
    ptr2 = test.find('A');
    test.insert_edge(31, ptr1, ptr2);
    //
    ptr1 = test.find('J');
    ptr2 = test.find('G');
    assert(test.insert_edge(13, ptr1, ptr2)==true);
    //
    ptr1 = test.find('A');
    ptr2 = test.find('G');
    assert(test.insert_edge(100, ptr1, ptr2)==true);
    //
    Debug("\t**Before**");
    test.print();
    assert(test.remove_node(ptr1)==true); // remove A
    Debug("\t**After**");
    test.print();
  }
  void test_dijkstra()
  {
    typedef Graph<char, int> graph;
    typedef graph::node node;
    typedef Dijkstra<graph> dijkstra;
    graph test;
    assert(test.insert_node('A')==true);
    assert(test.insert_node('B')==true);
    assert(test.insert_node('C')==true);
    assert(test.insert_node('X')==true);
    assert(test.insert_node('Y')==true);
    assert(test.insert_node('Z')==true);
    assert(test.insert_edge(11, test.find('A'), test.find('B'))==true);
    assert(test.insert_edge(7,  test.find('A'), test.find('C'))==true);
    assert(test.insert_edge(1,  test.find('B'), test.find('C'))==true);
    assert(test.insert_edge(4,  test.find('B'), test.find('X'))==true);
    assert(test.insert_edge(2,  test.find('C'), test.find('X'))==true);
    assert(test.insert_edge(8,  test.find('C'), test.find('Y'))==true);
    assert(test.insert_edge(6,  test.find('X'), test.find('Z'))==true);
    assert(test.insert_edge(5,  test.find('Y'), test.find('Z'))==true);
    test.print();
    //
    Debug("\n-------------");
    Debug("Shortest Path");
    Debug("-------------");
    dijkstra dijkstra_test;
    dijkstra::nvector result;
    dijkstra_test (test.find('A'), test.find('Z'), result);
    dijkstra::nvector::iterator i;
    for (i = result.begin(); i != result.end(); ++i)
       Debug( (*i)->get() );
    Debug("-------------");
  }
  void test_DFS()
  {
    typedef Graph<char, int> graph;
    typedef graph::node node;
    typedef DFS<graph> dfs;
    graph test;
    assert(test.insert_node('A')==true);
    assert(test.insert_node('B')==true);
    assert(test.insert_node('C')==true);
    assert(test.insert_node('X')==true);
    assert(test.insert_node('Y')==true);
    assert(test.insert_node('Z')==true);
    assert(test.insert_edge(1, test.find('A'), test.find('A'))==true);
    assert(test.insert_edge(1, test.find('A'), test.find('B'))==true);
    assert(test.insert_edge(1, test.find('A'), test.find('C'))==true);
    assert(test.insert_edge(1, test.find('B'), test.find('C'))==true);
    assert(test.insert_edge(1, test.find('B'), test.find('X'))==true);
    assert(test.insert_edge(1, test.find('C'), test.find('X'))==true);
    assert(test.insert_edge(1, test.find('C'), test.find('Y'))==true);
    assert(test.insert_edge(1, test.find('X'), test.find('Z'))==true);
    assert(test.insert_edge(1, test.find('Y'), test.find('Z'))==true);
    test.print();
    Debug("\n-------------");
    dfs dfs_test;
    dfs_test (test.find('A'));
    Debug("-------------");
  }
  void test_BFS()
  {
    typedef Graph<char, int> graph;
    typedef graph::node node;
    typedef BFS<graph> bfs;
    graph test;
    assert(test.insert_node('A')==true);
    assert(test.insert_node('B')==true);
    assert(test.insert_node('C')==true);
    assert(test.insert_node('X')==true);
    assert(test.insert_node('Y')==true);
    assert(test.insert_node('Z')==true);
    assert(test.insert_edge(1, test.find('A'), test.find('A'))==true);
    assert(test.insert_edge(1, test.find('A'), test.find('B'))==true);
    assert(test.insert_edge(1, test.find('A'), test.find('C'))==true);
    assert(test.insert_edge(1, test.find('B'), test.find('C'))==true);
    assert(test.insert_edge(1, test.find('B'), test.find('X'))==true);
    assert(test.insert_edge(1, test.find('C'), test.find('X'))==true);
    assert(test.insert_edge(1, test.find('C'), test.find('Y'))==true);
    assert(test.insert_edge(1, test.find('X'), test.find('Z'))==true);
    assert(test.insert_edge(1, test.find('Y'), test.find('Z'))==true);
    test.print();
    Debug("\n-------------");
    bfs bfs_test;
    bfs_test (test.find('A'));
    Debug("-------------");
  }
  void run()
  {
    Debug("\nTEST INSERTION");
    test_insertion();
    Debug("\nTEST REMOVE EDGE");
    test_edge_removal();
    Debug("\nTEST REMOVE NODE");
    test_node_removal();
    Debug("\nTEST DIJKSTRA");
    test_dijkstra();
    Debug("\nTEST DFS");
    test_DFS();
    Debug("\nTEST BFS");
    test_BFS();
  }
};

#endif // GRAPHTESTS_H

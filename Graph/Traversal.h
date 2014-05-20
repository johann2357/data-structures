#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>

struct STATUS
{
  bool data_ = false;
  bool operator() ()
  {
    return data_;
  }
  void on()
  {
    data_ = true;
  }
  void off()
  {
    data_ = false;
  }
};

template<class _G>
struct DFS
{
  typedef _G graph;
  typedef typename _G::N N;
  typedef typename _G::E E;
  typedef typename _G::node node;
  typedef std::unordered_map<node*, STATUS> map;
  void recursive(node* current, map& visited)
  {
    std::cout << current->get() << std::endl;
    visited[current].on();
    typename graph::eiterator eit;
    for (eit = (*current).begin(); eit != (*current).end(); ++eit)
    {
      if ( ((*eit).second == 0) && (!visited[(*eit).first->to()]()) )
        recursive((*eit).first->to(), visited);
    }
  }
  void operator() (node* from)
  {
    map visited;
    recursive(from, visited);
  }
};

template<class _G>
struct BFS
{
  typedef _G graph;
  typedef typename _G::N N;
  typedef typename _G::E E;
  typedef typename _G::node node;
  typedef std::unordered_map<node*, STATUS> map;
  void operator() (node* from)
  {
    map visited;
    std::queue<node*> currentLevel, nextLevel;
    //
    currentLevel.push(from);
    visited[from].on();
    bool end = true;
    while (!currentLevel.empty())
    {
      node* currNode = currentLevel.front();
      currentLevel.pop();
      std::cout << currNode->get() << "  ";
      typename graph::eiterator eit;
      for (eit = (*currNode).begin(); eit != (*currNode).end(); ++eit)
      {
        if ( ((*eit).second == 0) && (!visited[(*eit).first->to()]()) )
        {
          nextLevel.push((*eit).first->to());
          visited[(*eit).first->to()].on();
        }
      }
      end = false;
      if (currentLevel.empty())
      {
        std::cout << std::endl;
        if (end) 
          return;
        std::swap(currentLevel, nextLevel);
        end = true;
      }
    }
  }
};


#endif // TRAVERSAL_H

#ifndef GRAPH_DIJKSTRA_SHORTEST_PATH_H
#define GRAPH_DIJKSTRA_SHORTEST_PATH_H

#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <queue>

//! Dijkstra shortest path algorithm.
/*!
  Function object that takes a Graph Traits and 
  find the shortest path between 2 Nodes in a Graph.
  It also provided certain definitions that can be used to
  keep the code clean.
*/
template<class _G>
struct Dijkstra
{
  typedef _G graph;
  typedef typename _G::N N;
  typedef typename _G::E E;
  typedef typename _G::node node;
  //! A Node pointers vector.
  typedef std::vector<node*> nvector;
  typedef std::pair< E, nvector > pair;
  typedef std::unordered_map<node*, pair> map;
  //! Fill out a nvector with the shortest path between 2 nodes.
  /*!
    \param from The start Node pointer.
    \param to The end Node pointer.
    \param result The referenced vector that is going to be fill.
  */
  void operator() (node* from, node* to, nvector& result)
  {
    map visited;
    std::queue<node*> to_visit;
    to_visit.push(from);
    while ( !to_visit.empty() )
    {
      node* current = to_visit.front();
      E current_weight = visited[current].first;
      typename graph::eiterator eit;
      for (eit = (*current).begin(); eit != (*current).end(); ++eit)
      {
        if ( ((*eit).second == 0) && ((*eit).first->from() != to) )
        {
          if ((visited[(*eit).first->to()].second.empty()) || ((current_weight 
              + (*eit).first->weight()) < visited[(*eit).first->to()].first))
          {
            visited[(*eit).first->to()].second = visited[current].second;
            visited[(*eit).first->to()].second.push_back((*eit).first->from());
            visited[(*eit).first->to()].first = current_weight + 
                                                (*eit).first->weight();
            to_visit.push((*eit).first->to());
          }
        }
      }
      to_visit.pop();
    }
    if ( !visited[to].second.empty() )
    {
      visited[to].second.push_back(to);
      swap( visited[to].second, result );
    }
    return;
  }
};

#endif //GRAPH_DIJKSTRA_SHORTEST_PATH_H

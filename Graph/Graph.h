#ifndef GRAPH_H
#define GRAPH_H

#include <forward_list>
#include <utility>
#include <map>

//!  Graph's Node. 
/*!
  Takes a Graph Trait as a template parameter
*/
template<class G>
class Node
{
  template<typename _N, typename _E> friend class Graph;
  typedef typename G::N N;
  typedef typename G::edge edge;
  typedef typename G::EdgeCtnr EdgeCtnr;
  typedef typename G::eiterator eiterator;
  //! Private variable that stores the data of the node.
  N data_;
  //! Contains the edges comming in and out.
  /*!
    A std::map with an edge pointer as the key and bool as the value
    The bool is 0 if the edge is coming out of the actual node
    and 1 if the edge is coming from another node.
  */
  EdgeCtnr edges_;
  //! Default constructor.
  Node() {}
  //! Sets the data of the node while the Edge Container remains empty.
  /*!
    \param ndata An N type that is the data_ stored in the node.
  */
  Node(N ndata) 
  {
    data_ = ndata;
  }
  //! Node's Destructor
  virtual ~Node() {}
 public:
  //! Get the data already stored in the node.
  /*!
    \return The data of the Node.
  */
  N get()
  {
    return data_;
  }
  //! An iterator pointing at the begining of the Edge Container of the Node.
  /*!
    \return An Edge Container iterator.
  */
  eiterator begin()
  {
    return edges_.begin();
  }
  //! An iterator referring to the past-the-end element of the Edge Container.
  /*!
    \return An Edge Container iterator.
  */
  eiterator end()
  {
    return edges_.end();
  }
};

//!  Graph's Edge. 
/*!
  Takes a Graph Traits as a template parameter.
*/
template<class G>
class Edge
{
  template<typename _N, typename _E> friend class Graph;
  typedef typename G::E E;
  typedef typename G::node node;
  //! Stores the weight of the Edge.
  E data_;
  //! Stores the pointers of the Nodes that are coming from and coming to.
  /*!
    nodes_[0] is pointing to the nodes_[1].
  */
  node* nodes_[2];
  //! Set all the pointers NULL.
  Edge()
  {
    nodes_[0] = NULL;
    nodes_[1] = NULL;
  }
  //! Sets the Edge's weight and the Node pointers.
  /*!
    \param edata An E type that is the weight.
    \param from The nodes_[0].
    \param to The nodes_[1].
  */  
  Edge(E edata, node* from, node* to) 
  {
    data_ = edata;
    nodes_[0] = from;
    nodes_[1] = to;
  }
  //! Edge's Destructor.
  virtual ~Edge() {}
 public:
  //! The weight of the Edge.
  /*!
    \return Its weight.
  */
  E weight()
  {
    return data_;
  }
  //! The Node pointer that is coming from.
  /*!
    \return A Node pointer.
  */
  node* from()
  {
    return nodes_[0];
  }
  //! The Node pointer that is coming to.
  /*!
    \return A Node pointer.
  */
  node* to()
  {
    return nodes_[1];
  }
};

//!  Graph template. 
/*!
  Takes a N as a Node type and E as an Edge type as template parameters.
  It also serves as Traits to the Node and Edge.
*/
template<typename _N, typename _E>
class Graph
{
 public:
  typedef Graph<_N,_E> self;
  typedef _N N;
  typedef _E E;
  typedef Node<self> node;
  typedef Edge<self> edge;
  //! The container of all the Nodes in the Graph.
  typedef std::forward_list<node*> NodeCtnr;
  //! The container of all the Node's Edges.
  typedef std::map<edge*, bool> EdgeCtnr;
  //! The NodeCtnr iterator.
  typedef typename NodeCtnr::iterator niterator;
  //! The EdgeCtnr iterator.
  typedef typename EdgeCtnr::iterator eiterator;
 private:
  //! Contains all the Nodes in the Graph.
  NodeCtnr nodes_; 
 public:
  //! Creates an empty Graph.
  Graph() {}
  //! Destructor of the entire Graph.
  virtual ~Graph()
  {
    niterator nit;
    for (nit = nodes_.begin(); nit != nodes_.end(); ++nit)
    {
      eiterator eit;
      for (eit = (*nit)->edges_.begin(); eit != (*nit)->edges_.end(); ++eit)
        remove_edge((*eit).first);
      delete (*nit);
    } 
  }
  //! A Node pointer or NULL if it's not found.
  /*!
    \param ndata The Node's value.
    \return The Node's pointer if it's found in the Graph.
  */
  node* find(N ndata)
  {
    niterator nit;
    for (nit = nodes_.begin(); nit != nodes_.end(); ++nit)
      if ((*nit)->data_ == ndata)
        return (*nit);
    return NULL;
  }
  //! Insert a Node in the Graph if it doesn't exist.
  /*!
    \param ndata The value of the new Node if inserted.
    \return true if the insertion was successful.
  */
  bool insert_node(N ndata)
  {
    if (find(ndata) != NULL)
      return false;
    nodes_.push_front(new node(ndata));
    return true;
  }
  //! Insert an Edge in the Graph.
  /*!
    \param edata The weight of the new Edge if inserted.
    \param from The Node pointer that the Edge is coming from.
    \param to The Node pointer that the Edge is going to.
    \return true if the insertion was successful.
  */
  bool insert_edge(E edata, node* from, node* to)
  {
    if (!from && !to)
      return false;
    edge* tmp = new edge(edata, from, to);
    from->edges_.insert(std::make_pair(tmp, 0));
    to->edges_.insert(std::make_pair(tmp, 1));
    return true;
  }
  //! Remove the Edge.
  /*!
    \param ptr The Edge pointer that is going to be removed.
    \return true if the removal was successful.
  */
  bool remove_edge(edge* ptr)
  {
    if (!ptr)
      return false;
    node* tmp = ptr->nodes_[0];
    tmp->edges_.erase(ptr);
    tmp = ptr->nodes_[1];
    tmp->edges_.erase(ptr);
    delete ptr;
    ptr = NULL;
    return true;
  }
  //! Remove the Node and all its Edges.
  /*!
    \param ptr The Node pointer that is going to be removed.
    \return true if the removal was successful.
  */
  bool remove_node(node* ptr)
  {
    if (!ptr)
      return false;
    eiterator it;
    for (it = ptr->edges_.begin(); it != ptr->edges_.end(); ++it)
      remove_edge((*it).first);
    nodes_.remove(ptr);
    delete ptr;
    return true;
  }
  //! Prints out all the Nodes and its Edges.
  /*!
    Print a Node follow by its Edges indented.
    The arrow indicates whether the Edge is coming in <---(weight)---| 
    or coming out |---(weight)---> and the other Node.
  */
  void print()
  {
    niterator nit;
    for (nit = nodes_.begin(); nit != nodes_.end(); ++nit)
    {
      std::cout << (*nit)->data_ << " :\n";
      eiterator eit;
      for (eit = (*nit)->edges_.begin(); eit != (*nit)->edges_.end(); ++eit)
      {
        std::cout << "   ";
        if ((*eit).second)
          std::cout << "<-- " << (*eit).first->data_ << " --| ";
        else
          std::cout << "|-- " << (*eit).first->data_ << " --> ";
        std::cout << (*eit).first->nodes_[!(*eit).second]->data_ << "\n";
      }
    }
  }
  //! An iterator pointing at the begining of the Node Container of the Graph.
  /*!
    \return A Node Container iterator.
  */
  niterator begin()
  {
    return nodes_.begin();
  }
  //! An iterator referring to the past-the-end element of the Node Container.
  /*!
    \return A Node Container iterator.
  */
  niterator end()
  {
    return nodes_.end();
  }
};

#endif // GRAPH_H

#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

template <typename T>
class Node;
template <class Tr>
class BinTreeIterator;
template <typename T, class Tr>
class BinTree;

template <typename _T>
struct Forward
{
  typedef _T T;
  typedef Node<T> node;
  typedef std::pair< int, node* > pair;
  typedef std::stack<pair> stack;
  typedef Forward<T> self;
  enum state { L, R };
};

template <typename _T>
struct Reverse
{
  typedef _T T;
  typedef Node<T> node;
  typedef std::pair< int, node* > pair;
  typedef std::stack<pair> stack;
  typedef Reverse<T> self;
  enum state { R, L };
};

template <class Tr>
struct Inorder
{
  typedef typename Tr::T T;
  typedef typename Tr::node node;
  typedef typename Tr::stack stack;
  typedef Inorder<Tr> I;
  enum state { L_=Tr::L, R_=Tr::R, S_=2, U_=3 };
  state operator() (stack& stack_)
  {
    if (stack_.top().first == S_)
    {
      stack_.top().first = R_;
      if ( operator() (stack_, stack_.top().second->leaf_[R_]) )
        return S_;
    }
    else if (stack_.top().first == L_)
    {
      stack_.top().first = S_;
      return S_;
    }
    return U_;
  }
  bool operator() (stack& stack_, node* tmp)
  {
    if (tmp)
    {
      do
      {
        stack_.push( std::make_pair(L_, tmp) );
        tmp = tmp->leaf_[L_];
      } while (tmp);
      stack_.top().first = S_;
      return true;
    }
    return false;
  }
};

template <class Tr>
struct Preorder
{
  typedef typename Tr::T T;
  typedef typename Tr::node node;
  typedef typename Tr::stack stack;
  typedef Preorder<Tr> I;
  enum state { L_=Tr::L, R_=Tr::R, S_=2, U_=3 };
  state operator() (stack& stack_)
  {
    if (stack_.top().first == U_ || stack_.top().first == R_)
      return U_;
    else if (stack_.top().first == S_)
    {
      stack_.top().first = L_;
      if ( operator() (stack_, stack_.top().second->leaf_[L_]) )
        return S_;
    }
    else if (stack_.top().first == L_)
    {
      stack_.top().first = R_;
      if ( operator() (stack_, stack_.top().second->leaf_[R_]) )
        return S_;
    }
  }
  bool operator() (stack& stack_, node* tmp)
  {
    if (tmp)
    {
      stack_.push( std::make_pair(S_, tmp) );
      return true;
    }
    return false;
  }
};

template <class Tr>
struct Postorder
{
  typedef typename Tr::T T;
  typedef typename Tr::node node;
  typedef typename Tr::stack stack;
  typedef Postorder<Tr> I;
  enum state { L_=Tr::L, R_=Tr::R, S_=2, U_=3 };
  state operator() (stack& stack_)
  {
    if (stack_.top().first == S_)
      return U_;
    else if (stack_.top().first == R_)
    {
      stack_.top().first = S_;
      return S_;
    }
    else if (stack_.top().first == L_)
    {
      stack_.top().first = R_;
      if ( operator() (stack_, stack_.top().second->leaf_[R_]) )
        return S_;
      else
      {
        stack_.top().first = S_;
        return S_;
      }
    }
  }
  bool operator() (stack& stack_, node* tmp)
  {
    if (tmp)
    {
      do
      {
        do
        {
          stack_.push( std::make_pair(L_, tmp) );
          tmp = tmp->leaf_[L_];
        } while (tmp);
        if (!stack_.empty())
        {
          stack_.top().first = R_;
          tmp = stack_.top().second->leaf_[R_];
        }
      } while( tmp );
      stack_.top().first = S_;
      return true;
    }
    return false;
  }
};

#endif // ITERATOR_TRAITS_H

/*
  Pre-Order:     Root   , Left child ,   Right child.
  In-Order:   Left child,    Root    ,   Right child.
  Post-Order: Left Child, Right child,     Root.
*/
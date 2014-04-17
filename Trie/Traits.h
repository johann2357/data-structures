#ifndef TRAITS_H
#define TRAITS_H

template <typename T>
struct Less
{
  bool operator() (T a, T b)
  {
    return (a < b);
  }
};

template <typename T>
struct Greater
{
  bool operator() (T a, T b)
  {
    return (a > b);
  }
};

template <typename _T>
struct TraitsDescendant
{
  typedef _T T;
  typedef Greater<T> C;
};

template <typename _T>
struct TraitsAscendant
{
  typedef _T T;
  typedef Less<T> C;
};

#endif // TRAITS_H

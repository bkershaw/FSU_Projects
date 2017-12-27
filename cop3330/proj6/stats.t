/*
  stats.t
  Blake Kershaw
  10/31/15
  kershaw
  version 2.1
*/

#ifndef STATS_T
#define STATS_T

#include <iostream>
#include <vector>

template < typename T >
long double Mean (const std::vector<T>& v);  // returns mean of elements of v

template < typename T >
long double Median (std::vector<T>& v);  // returns median of elements of v

template < typename T >
void SelectionSort (std::vector<T>& v);  // sorts elements of v

template < typename T >
void Swap (T& x, T& y);  // interchanges values of x and y

template < typename T >
long double Mean(const std::vector<T>& v)
{
  long double total = 0;
  for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
  {
    total += *i;
  }
  return (total / v.size());
}

template < typename T >
long double Median(std::vector<T>& v)
{
  SelectionSort(v);
  if ((v.size() % 2) == 1)
    return (v [ ( (v.size() + 1 ) / 2 ) - 1 ] );
  else
 {
    return (v[(v.size() / 2)] + v[(v.size() / 2) - 1]) / 2.0;
 }
}

template < typename T >
void Swap ( T& x, T& y)
{
  T temp;
  temp = x;
  x = y;
  y = temp;
}

template < typename T >
void SelectionSort(std::vector<T>& v)
{
  for (size_t i = 1; i < v.size(); ++i)
  {
    T currentValue = v[i];
    size_t element = i;
    while (element > 0 && currentValue < v[element - 1])
    {
      v[element] = v[element - 1];
      --element;
    } //end while loop
    Swap (v[element], currentValue);
  } //end for loop
}

#endif

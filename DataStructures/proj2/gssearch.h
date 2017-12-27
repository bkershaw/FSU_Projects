/*
gssearch.h
Blake Kershaw
CS Username: kershaw
January 30th 2017
*/

#ifndef GSSEARCH_H
#define GSSEARCH_H

#include <compare_spy.h> 

namespace seq
{
  // return upper bound of T
  template < class I, typename T, class P >
    I g_lower_bound(I beg, I end, const T& val, P& cmp)
  {
    while (beg != end)
    {
      if (!cmp(*beg, val)) 
        return beg; 
      ++beg;
    }
    return beg; 
  }

  // return upper bound of T
  template < class I, typename T, class P>
    I g_upper_bound(I beg, I end, const T& val, P& cmp)
  {
    while (beg != end)
    {
      if (cmp(val, *beg)) 
        return beg; 
      ++beg;
    }
    return beg; 
  }

} //namespace seq

#endif

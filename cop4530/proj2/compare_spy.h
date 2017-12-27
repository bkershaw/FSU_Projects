/*
compare_spy.h
Blake Kershaw
COP4530
January 27th, 2017
*/

#ifndef COMPARE_SPY_H
#define COMPARE_SPY_H

namespace fsu
{
  template <typename T>
  class LessThanSpy
  {
public:

    //Default constructor
    LessThanSpy(): count_(0)
    {}  

    //returns true if and only if t1 < t2, where T is the template paramter 
    //overload ()
    bool operator() (const T& t1, const T& t2)
    {
      ++count_;
      return (t1 < t2);      
    }
  
    //Sets the internal count to zero
    void Reset()
    {
      count_ = 0;
    }

    // Returns the number of times operator() is called since the object was
    // created or the last time Reset was called. 
    size_t Count() const
    {
      return count_;
    }

  private:
    size_t count_;

  }; //LessThanSpy 

} //namespace fsu

#endif

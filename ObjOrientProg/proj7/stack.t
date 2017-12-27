/*
stack.t
Blake Kershaw
November 16, 2015
*/


#ifndef STACK_T
#define STACK_T

#include <iostream>

namespace fsu {

  template < typename T, size_t N = 100> // default array size = 100
  class Stack
  {
  public:
    // Stack < T , N > API
    Stack             ();             // default constructor
    Stack             (T fill);       // puts "fill" in each slot of the underlying array (keeps size = 0)
    Stack             (const Stack&); // copy constructor
    ~Stack            () {};          // destructor
    Stack& operator = (const Stack&); // assignment operator

    void     Push     (const T& t); // push t onto stack; error if full
    T        Pop      ();           // pop stack and return removed element; error if stack is empty
    T&       Top      ();           // return top element of stack; error if stack is empty
    const T& Top      () const;     // const version
    size_t   Size     () const;     // return number of elements in stack
    size_t   Capacity () const;     // return storage capacity [maximum size] of stack
    bool     Empty    () const;     // return 1/true if stack is empty, 0/false if not empty
    void     Clear    ();           // make the stack empty
    void     Display  (std::ostream& os, char ofc = '\0') const; // output stack contents through os
    void     Dump     (std::ostream& os); // output all private data (for development use only)

  private:
    const size_t capacity_;  // = N = size of array   - fixed during life of stack
    T            data_[N];   // array of T objects    - where T objects are stored
    size_t       size_;      // current size of stack - dynamic during life of stack

  };

  // Output << overloader
  template < typename T, size_t N >
  std::ostream& operator << (std::ostream& os, const Stack<T, N>& S);

  //constructor
  template <typename T, size_t N >
  Stack<T, N>::Stack()
    : capacity_(N), data_(), size_(0)
  {}

  // copy constructor
  template <typename T, size_t N >
  Stack<T, N>::Stack(const Stack& stackCopy)
    : capacity_(stackCopy.capacity_), data_(), size_(stackCopy.size_)
  {
    for (size_t i = 0; i < N; ++i)
      data_[i] = stackCopy.data_[i];
  }

  // fill constructor
  template <typename T, size_t N >
  Stack<T, N>::Stack(T fill)
    : capacity_(N), data_(), size_(0)
  {
    for (size_t i = 0; i < N; ++i)
      data_[i] = fill;
  }

  // assignment operator
  template <typename T, size_t N >
  Stack<T,N>& Stack<T, N>::operator= (const Stack& assignStack)
  {
    if (&assignStack != this)
    {
      size_ = assignStack.size_;
      for (size_t i = 0; i < N; ++i)
        data_[i] = assignStack.data_[i];
    }
    return *this;
  }

  //void push
  template <typename T, size_t N >
  void Stack<T, N>::Push(const T& t)
  {
    if (size_ < N)
    {
      data_[size_] = t;
      ++size_;
    }
  }
  
  //Empty
  template <typename T, size_t N >
  bool Stack<T, N>::Empty() const
  {
    if (size_ == 0)
      return true;
    return false;
  }

  //Pop
  template <typename T, size_t N >
  T Stack<T, N>::Pop()
  {
    if (size_ > 0)
    {
      T pop = data_[size_];
      --size_;
      return pop;
    }
    std::cerr << "Cannot pop, stack is empty!" << std::endl;
    exit(EXIT_FAILURE);
  }

  //Top
  template <typename T, size_t N >
  T& Stack<T, N>::Top()
  {
    if (size_ > 0)
      return data_[size_ -1];
    std::cerr << "Cannot return top, stack is empty!" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // Const Top
  template <typename T, size_t N >
  const T& Stack<T, N>::Top() const
  {
    if (size_ > 0)
      return data_[size_ -1];
    std::cerr << "Cannot return top, stack is empty!" << std::endl;
    exit(EXIT_FAILURE);
  }

  //Size
  template <typename T, size_t N >
  size_t Stack<T, N>::Size() const
  {
    return size_;
  }

  //Capacity
  template <typename T, size_t N >
  size_t Stack<T, N>::Capacity() const
  {
    return capacity_;
  }

  //Clear
  template <typename T, size_t N >
  void Stack<T, N>::Clear()
  {
    size_ = 0; // could also set them all to null just to be thorough
  }

  //Display
  template <typename T, size_t N >
  void Stack<T, N>::Display(std::ostream& os, char ofc ) const
  {
    if ( (ofc != '\0') && (size_ != 0)) 
    {
      os << ofc;
      for (size_t i = 0; i < (size_ - 1); ++i)
        os << data_[i] << ofc;
      os << data_[size_ - 1]; 
      return;
    }
    
    for (size_t i = 0; i < size_; ++i)
      os << data_[i];
  }

  //Dump
  template <typename T, size_t N >
  void Stack<T, N>::Dump(std::ostream& os)
  {
    std::cout
      << "Capacity: " << capacity_ << '\n'
      << "Size:     " << size_ << '\n'
      << "Array:    " << '[';
    for (size_t i = 0; i < (capacity_ - 1); ++i)
      os << data_[i] << ',';
    os << data_[capacity_ - 1]; // No ofc char after last element
    std::cout << ']' << '\n'
      << "Stack:    " << '[';
    Display(std::cout, ',');
      std::cout << "]";
  }

  //output << overloader
  template < typename T, size_t N >
  std::ostream& operator << (std::ostream& os, const Stack<T, N>& S)
  {
    S.Display(os, '\0');
    return os;
  }
}
#endif

/*
    constTest.cpp

    testing the const and non-const versions of Top and Front 
*/

#include <stack.t>
#include <queue.t>

char ShowTop(const fsu::Stack<char>& s)
{
  return s.Top();
}

void ChangeTop(fsu::Stack<char>& s, char newTop)
{
  s.Top() = newTop;
}

char ShowFront(const fsu::Queue<char>& s)                                                      
{
  return s.Front();
}

void ChangeFront(fsu::Queue<char>& s, char newFront)
{
  s.Front() = newFront;
}

int main()
{
  fsu::Stack<char> s;
  fsu::Queue<char> q;
  s.Push('A');
  q.Push('B');
  std::cout << ShowTop(s)<< ' ' << ShowFront(q) << '\n';
  ChangeTop(s,'a');
  ChangeFront(q,'b');
  std::cout << ShowTop(s)<< ' ' << ShowFront(q) << '\n';
  return 0;
}

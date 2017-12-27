/*
    constTest.cpp

    testing the const and non-const versions of Top
*/

#include <stack.t>

char ShowTop(const fsu::Stack<char>& s)
{
  return s.Top();
}

void ChangeTop(fsu::Stack<char>& s, char newTop)
{
  s.Top() = newTop;
}

int main()
{
  fsu::Stack<char> s;
  s.Push('A');
  std::cout << ShowTop(s) << '\n';
  ChangeTop(s,'a');
  std::cout << ShowTop(s) << '\n';
  return 0;
}

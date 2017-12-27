/**
   test.cpp

   test harness for UIntSet
*/

#include <cstdlib>
#include <iostream>
#include <uintset.h>
// #include <uintset.cpp> // in lieu of makefile
// #include <bitvect.cpp> // in lieu of makefile

void ShowSetInfo (const UIntSet& s)
{
  std::cout << "       Range() = " << s.Range() 
	    << ", Size() = "          << s.Size() 
	    << ", Empty() = "         << (s.Empty() ? "true" : "false") << '\n';
}

int main()
{
  UIntSet s1(21), s2(21), s3(21);
  std::cout << " sets after declaration:\n"; 
  std::cout << "  s1 = " << s1 << '\n'; ShowSetInfo(s1);
  std::cout << "  s2 = " << s2 << '\n'; ShowSetInfo(s2);
  std::cout << "  s3 = " << s3 << '\n'; ShowSetInfo(s3);

  for (size_t i = 0; i < 21; ++i) 
    s1.Insert(i);
  for (size_t i = 0; i < 21; i+=2) 
    s2.Insert(i);
  for (size_t i = 0; i < 21; i+=3) 
    s3.Insert(i);

  std::cout << " sets after insertions:\n"; 
  std::cout << "  s1 = " << s1 << '\n'; ShowSetInfo(s1);
  std::cout << "  s2 = " << s2 << '\n'; ShowSetInfo(s2);
  std::cout << "  s3 = " << s3 << '\n'; ShowSetInfo(s3);
  s1 -= s3;
  std::cout << " after s1 -= s3:\n"; 
  std::cout << "  s1 = " << s1 << '\n'; ShowSetInfo(s1);
  std::cout << "  s3 = " << s3 << '\n'; ShowSetInfo(s3);

  std::cout << " set operations:\n"; 
  std::cout << "  s2 + s3 = " << s2 + s3 << '\n';
  std::cout << "  s2 * s3 = " << s2 * s3 << '\n';
  std::cout << "  s2 - s3 = " << s2 - s3 << '\n';

  std::cout << " assignments:\n";
  s1 = s2 + s3;  std::cout << "  s1 = s2 + s3: " << s1 << '\n'; ShowSetInfo(s1);
  s1 = s2 * s3;  std::cout << "  s1 = s2 * s3: " << s1 << '\n'; ShowSetInfo(s1);
  s1 = s2 - s3;  std::cout << "  s1 = s2 - s3: " << s1 << '\n'; ShowSetInfo(s1);

  for (size_t i = 0; i < 9; ++i)
  {
    s1.Remove(i);
    s2.Remove(i);
    s3.Remove(i);
  }
  std::cout << " after removing 0 - 8:\n";
  std::cout << "  s1 = " << s1 << '\n'; ShowSetInfo(s1);
  std::cout << "  s2 = " << s2 << '\n'; ShowSetInfo(s2);
  std::cout << "  s3 = " << s3 << '\n'; ShowSetInfo(s3);

  s1.Clear(); s2.Clear(); s3.Clear();
  std::cout << " after Clear():\n";
  std::cout << "  s1 = " << s1 << '\n'; ShowSetInfo(s1);
  std::cout << "  s2 = " << s2 << '\n'; ShowSetInfo(s2);
  std::cout << "  s3 = " << s3 << '\n'; ShowSetInfo(s3);
}

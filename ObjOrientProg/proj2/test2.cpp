/**
   test2.cpp

   test2 harness for class Product
   specifically tests for ownership of data pointed to by name_
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <product.h>

int main()
{
  char      name1 [10]   = "product_1";
  uint32_t  code1        = 0xFEDCBA98;
  float     cost1        = 100.0;

  char      name2 [10] = "product_2";
  uint32_t  code2      = 0x89ABCDEF;
  float     cost2      = 200.0;

  char      name3 [10] = "!ERROR!_3";
  uint32_t  code3      = 0x00000000;
  float     cost3      = 0.0;

  Product p1(name1, code1, cost1), p2(name2,code2, cost2);
  std::cout << " Products after declaration:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';

  strcpy (name1,name3);  // copy name3 to name1
  strcpy (name2,name3);  // copy name3 to name2
  code1 = code3;         // copy code3 to code1
  code2 = code3;         // copy code3 to code2
  cost3 = cost2;         // copy cost3 to cost1
  cost2 = cost3;         // copy cost3 to cost2

  std::cout << " Products after client program changes name, code, and cost variables:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';
}

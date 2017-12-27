/**
   test.cpp

   test harness for class Product
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <product.h>
// #include <product.cpp> // in lieu of makefile

const size_t arraySize = 10;
const size_t numDigits = 2; 

Product CopyCheck (Product p);
void AssignCheck (const Product& pIn, Product& pOut);

Product CopyCheck (Product p)  // pass in by value calls CC
{
  Product x(p);  // initialization calls CC (NOT assignment!)
  return x;  // return by value calls CC
}

void AssignCheck (const Product& pIn, Product& pOut)  // pass in by reference - no copies made
{
  pOut = pIn;  // calls assignment (not CC)
}

int main()
{
  Product p1("hammer", 0xFFFFFFFF, 15.00), p2;
  std::cout << " Products after declaration:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';

  p1.SetName("Copy Checker");
  p1.SetCost(10.0);
  p2.SetName("Assign Checker");
  p2.SetCost(20.0);
  std::cout << " Products after Set:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';

  
  Product p3 = CopyCheck(p1);
  std::cout << " Products after p3 = CopyCheck(p1):\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p3 = " << p3 << '\n';
  
  AssignCheck(p2, p3);
  std::cout << " Products after AssignCheck(p2,p3):\n"; 
  std::cout << "  p2 = " << p2 << '\n';
  std::cout << "  p3 = " << p3 << '\n';
  
  Product p4 ("Transitive Assignment Check", 50, 25.0);
  p1 = p2 = p3 = p4;
  std::cout << " Products after p1 = p2 = p3 = p4:\n"; 
  std::cout << "  p1 = " << p1 << '\n';
  std::cout << "  p2 = " << p2 << '\n';
  std::cout << "  p3 = " << p3 << '\n';
  std::cout << "  p4 = " << p4 << '\n';
  
  Product * parray = new Product [arraySize];
  std::cout << " Product Array after declaration:\n";
  for (size_t i = 0; i < arraySize; ++i)
  {
    std::cout << "  p[" << std::setw(numDigits) << i << "] = " << parray[i] << '\n';
  } 

  for (size_t i = 0; i < arraySize; ++i)
  {
    parray[i].SetName("Titanium Hammer");
    parray[i].SetBarCode(static_cast<uint32_t>(17 + i));
    parray[i].SetCost(static_cast<float>((2*17 + i))/2);
  } 
  std::cout << " Product Array after Set:\n";
  for (size_t i = 0; i < arraySize; ++i)
  {
    std::cout << "  p[" << std::setw(numDigits) << i << "] = " << parray[i] << '\n';
  } 

   
}

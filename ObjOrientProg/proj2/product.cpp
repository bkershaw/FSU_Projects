/*
product.cpp
September 10th 2015
Blake Kershaw
kershaw
*/

#include <product.h>
#include <cstring>
#include <iomanip>

void Product::SetName    ( const char* name )
{
  if (name_ != NULL)
    delete [] name_;
  size_t size = strlen(name); //size of incoming cstring
  name_ = new char [1 + size];
  name_[size] = '\0';
  strcpy(name_, name); // copy name into new string character by character  
}

void Product::SetBarCode ( uint32_t code )
{
  code_ = code;
}

void Product::SetCost    ( float cost )
{
  cost_ = cost;
}

const char* Product::GetName    () const
{
  return name_;
}

uint32_t Product::GetBarCode () const
{
  return code_;
}

float Product::GetCost    () const
{
  return cost_;
}

Product::Product() : name_(NULL), code_(0), cost_(0.0)
{
  name_ = new char [2];
  name_[0] = '#';
  name_[1] = '\0';   
}

Product::Product (const char* name, uint32_t code, float cost): name_(NULL), code_(code), cost_(cost)
{
//proceed as in SetName, except dont worry about delete (use incoming name for the name)

  size_t size = strlen(name);
  name_ = new char [ 1 + size ];
  name_[size] = '\0';
  strcpy(name_, name);

}

Product::~Product ()
{
  if (name_ != NULL)
    delete [] name_;
}

Product::Product (const Product& p) : name_(NULL), code_(p.code_), cost_(p.cost_)
{
// proceed as in SetName, except dont wory about delete
  size_t size = strlen(p.GetName());
  name_ = new char [1 + size];
  name_[size] = '\0';
  strcpy(name_, p.GetName());   
}

Product& Product::operator= (const Product& p)
{
  if (this != &p)
  {
    if (name_ != NULL)
      delete [] name_;
    size_t size = strlen(p.GetName());
    name_ = new char [1 + size];
    name_[size] = '\0';
    strcpy(name_, p.GetName());
    cost_=p.GetCost();
    code_=p.GetBarCode();
}
  return *this;
}

std::ostream& operator << (std::ostream& os, const Product& p)
{
  std::ios_base::fmtflags flags = os.flags();
  os.setf(std::ios::fixed | std::ios::showpoint); // prep for $ output
  os.precision(2);
  os << p.GetName() << '\t'
     << std::hex << std::uppercase << std::setfill('0') << std::setw(8) 
     << p.GetBarCode()
     << std::dec << std::setfill(' ') << '\t'          
     << p.GetCost();
  os.setf(flags); // return flags to previous states
  return os;
}

/*
uintset.cpp
September 30, 2015
Blake Kershaw
kershaw
 */

#include <iostream>

#include <uintset.h>
#include <bitvect.h>

using namespace fsu;

UIntSet::UIntSet(unsigned long size) : bv_(size)
{
}

UIntSet::UIntSet(const UIntSet& s) : bv_(64)
{
  if (this != &s) {
    bv_ = s.bv_;
  }
}

UIntSet& UIntSet::operator =(const UIntSet& s)
{
  if (this != &s)
    bv_ = s.bv_;

  return *this;
}

UIntSet::~UIntSet()
{
}

//services

void UIntSet::Dump(std::ostream& os)const
{
  bv_.Dump(os);
}

void UIntSet::Insert(unsigned long n)
{
  bv_.Set(n);
}

void UIntSet::Remove(unsigned long n)
{
  bv_.Unset(n);
}

void UIntSet::Clear()
{
  bv_.Unset();
}

bool UIntSet::Member(unsigned long n) const
{
  return bv_.Test(n);
}

bool UIntSet::Empty() const
{
  return Size() == 0;
}

size_t UIntSet::Size() const
{
 size_t counter = 0;
for(size_t i = 0; i < bv_.Size(); ++i)
 {
   counter += bv_.Test(i);
 }
return counter;
}

size_t UIntSet::Range() const
{
  return bv_.Size();
}

UIntSet& UIntSet::operator +=(const UIntSet& s)
{
  for (size_t i = 0; i < s.Range(); ++i)
  {
    if (s.Member(i))
      Insert(i);
  }
  return *this;
}

UIntSet& UIntSet::operator *=(const UIntSet& s)
{
  for (size_t i = 0; i < s.Range(); ++i)
  {
    if (s.Member(i) && Member(i))
      Insert(i);
    if(! s.Member(i))
      Remove(i);
  }
  return *this;
}

UIntSet& UIntSet::operator -=(const UIntSet& s)
{
  for (size_t i = 0; i < s.Range(); ++i)
  {
    if (s.Member(i))
      Remove(i);
  }
  return *this;
}

// Global Operators

UIntSet operator +(const UIntSet& s1, const UIntSet& s2)
{
  UIntSet s(s1);
  s += s2;
  return s;
}

UIntSet operator *(const UIntSet& s1, const UIntSet& s2)
{
  UIntSet s(s1);
  s *= s2;
  return s;
}

UIntSet operator -(const UIntSet& s1, const UIntSet& s2)
{
  UIntSet s(s1);
  s -= s2;
  return s;
}

bool operator ==(const UIntSet& s1, const UIntSet& s2)
{
  UIntSet s;
  for (size_t i = 0; i < s.Range(); ++i)
  {
    if (s1.Member(i) == s2.Member(i))
      return true;
  }
  return false;
}

bool operator !=(const UIntSet& s1, const UIntSet& s2)
{
  UIntSet s;
  for (size_t i = 0; i < s.Range(); ++i)
  {
    if (s1.Member(i) == s2.Member(i))
      return true;
  }
  return false;
}

std::ostream& operator <<(std::ostream& os, const UIntSet& s)
{
  os << '{';
  for (size_t i = 0; i < s.Range(); ++i)
    if (s.Member(i))
      os << ' ' << i;
  os << " " << '}';
  return os;
}

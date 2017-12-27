/*
  stats.cpp
  Blake Kershaw
  9/4/2015
  version 1.8
*/

#include <iostream>
#include <stats.h>

float Mean (const int* array, size_t size) // calculates mean of data in array
{
  float sum = 0;
  if(size == 0)
    return 0;
  for (size_t i = 0; i < size; ++i)
  {
    sum += array[i];
  }
  return (sum / size );
}

float Median (int* array, size_t size) // calculates median of data in array
{
  Sort(array,size);
  if(size % 2 !=0)
    return array[size/2];
  unsigned long int hold = size/2;
  return static_cast<float> (array[hold] + array[hold - 1]) / 2.0;
}

void Swap (int& x, int& y) // interchanges values of x and y
{
  int temp;
  temp = x;
  x = y;
  y = temp;
}

void Sort (int* array, size_t size) // sorts the data in array
{
  unsigned int smallest; //index of smallest element

  for(unsigned int i = 0; i < size; ++i)
  {
    smallest = i; //first index of remaining array

    for(unsigned int index = i + 1; index < size; ++index)
    {
      if(array[index] < array[smallest])
        smallest = index;
    } //end of second loop
    Swap(array[i], array[smallest]);
  } //end of first loop
} //end of sort function

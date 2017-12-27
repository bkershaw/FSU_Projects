/*
  stats.h
  Blake Kershaw
  8/28/2015
  version 1.0
*/

#ifndef STATS_H_
#define STATS_H_

float Mean   (const int* array, size_t size); // calculates mean of data
float Median (int* array, size_t size);       // calculates median of data
void  Swap   (int& x, int& y);                // interchanges values of x and y
void  Sort   (int* array, size_t size);       // sorts the data in array

#endif 

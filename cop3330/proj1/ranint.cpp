/*
    ranint.cpp
    09/02/12
    Chris Lacher

    creates random string data for testing 

    Copyright 2012, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>

#include <xran.h>
// #include <xran.cpp> // in lieu of makefile

int main( int argc , char * argv[] )
{
  if (argc != 4)
  {
    std::cout << " ** required arguments:\n"
	      << "     1: filename\n"
	      << "     2: upper bound on absolute size ('0' means no upper bound)\n"
	      << "     3: count of items\n"
	      << " ** try again\n";
    return 0;
  }

  char* outfile     = argv[1];
  long   upperBound = atol(argv[2]);
  long   lowerBound;
  size_t count      = atol(argv[3]);
  if (upperBound == 0)
  {
    upperBound = INT_MAX;
    lowerBound = INT_MIN;
  }
  else
  {
    lowerBound = upperBound - 2*upperBound;
  }

  std::ofstream out1(outfile);
  if (out1.fail())
  {
    std::cout << " ** cannot open file " << outfile << '\n'
	      << " ** try again\n";
    return 0;
  }

  fsu::Random_int ranint;

  for (size_t i = 0; i < count; ++i)
  {
    out1 << ranint(lowerBound, upperBound) << '\n';
  }
  out1.close();

  std::cout << "Results stored in file " << outfile << '\n'
	    << "  range: " << lowerBound << " .. " << upperBound - 1 << '\n'
	    << "  count: " << count << '\n';
  return 0;
}

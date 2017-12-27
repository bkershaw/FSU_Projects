/**************************************************************
 *                                                            *
 *               Name: Blake Kershaw                          *
 *                Class: COP 4020                             * 
 *       Assignment: Project 3(Implmenting Cparse)            *
 *        Compile: "g++ -std=c++11 -o cparse.exe cparse.cpp"  *  
 *                                                            *
 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <set>
#include <vector>
#include <list>

struct  {
};


int main()
{
  int lr = 0;
  int l = 0;
  int map = 0;
  char temp;
  char line[20] = {0}; 
  std::vector <std::string> input; // holds grammer rules
  int inputCounter = 0;
  int itemCounter = 1;
 
  /*read input file line by line */
  while(fgets(line,20,stdin)){

    input.push_back(line); // place incoming grammar rules into list
    ++inputCounter; //increment counter

  } // end while fgets
 
  std::cout << "Augmented Grammar" << std::endl;
  std::cout << "-----------------" << std::endl;

  std::cout << "\nSetsof LR(0) Items" << std::endl;
  std::cout << "------------------" << std::endl;

 return 0;
} // end main


/*
    fuintset.cpp
    01/27/15
    Chris Lacher

    command line arguments:

    1: upper bound of range (required)
    2: batch (optional)
     
    Copyright 2015, R.C. Lacher
*/

#include <cctype>  // tolower()
#include <iostream>
#include <fstream>

#include <uintset.h>
// #include <uintset.cpp>
// #include <bitvect.cpp>

// prototypes of functions implemented after main()
void Preamble();
void DisplayMenu();
void GetCommands
  (
    char& c1, char& c2, char& c3, char& c4, char& c5,  // command characters (5 deep)
    unsigned long& t, unsigned long upperbound,        // command arguments
    std::istream* p, bool BATCH                        // input control
    );
void BadCommand(std::istream* p);

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << " ** command line arguments:\n"
              << "    1: upper bound for universe [required]\n"
	      << "    2: name of command file [optional - for processing a file of commands]\n";
    return 0;
  }
  unsigned long upperbound = atoi(argv[1]);

  std::ifstream ifs;
  std::istream* isptr = &std::cin;
  bool BATCH = 0;  

  if (argc > 2)
  {
    ifs.open(argv[2]);
    if (ifs.fail())
    {
      std::cout << " ** unable to read file \"" << argv[2] << "\"\n"
                << "    try again\n";
      exit(0);
    }
    isptr = &ifs;
    BATCH = 1;
  }

  Preamble();
  if (!BATCH) DisplayMenu();
  UIntSet x1(upperbound), x2(upperbound), x3(upperbound);
  upperbound = x1.Range();
  unsigned long t;
  char c1, c2, c3, c4, c5;  // longest command 1=3+5
  do
  {
    std::cout << "Enter command ('M' for menu, 'Q' to quit): ";
    GetCommands (c1,c2,c3,c4,c5,t,upperbound,isptr,BATCH);

    switch (c1)
    {
      case '1':
      // ************************************************************* //
      //     general case c1 = '1'
      // ************************************************************* //

        switch (c2)
        {
        // ***************************************************************** //
        //     1 = n, 1 = m op n  [ ops: +, *, -, <, <=, ==, !=, >=, > ]     //
        // ***************************************************************** //

          case '!':
            switch(c4)
            {
              case '1':
                if (x1 != x1)
                  std::cout << "x1 != x1 is TRUE\n";
                else
                  std::cout << "x1 != x1 is FALSE\n";
                break;
              case '2':
                if (x1 != x2)
                  std::cout << "x1 != x2 is TRUE\n";
                else
                  std::cout << "x1 != x2 is FALSE\n";
                break;
              case '3':
                if (x1 != x3)
                  std::cout << "x1 != x3 is TRUE\n";
                else
                  std::cout << "x1 != x3 is FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;        

          case '=':   // case 1=
            switch (c3)    
            {
              case '1': // case '1=1?'
                switch(c4)
                {
                  case '\n': // case '1=1'
                    x1 = x1; break;
                  case '+':  // case '1=1+?'
                    switch(c5)
                    {
                      case '1':
                        x1 = x1 + x1; break;
                      case '2':
                        x1 = x1 + x2; break;
                      case '3':
                        x1 = x1 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':  // case '1=1*?'
                    switch(c5)
                    {
                      case '1':
                        x1 = x1 * x1; break;
                      case '2':
                        x1 = x1 * x2; break;
                      case '3':
                        x1 = x1 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':  // case '1=1-?'
                    switch(c5)
                    {
                      case '1':
                        x1 = x1 - x1; break;
                      case '2':
                        x1 = x1 - x2; break;
                      case '3':
                        x1 = x1 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
             
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 1=1

              case '2': // case '1=2'
                switch(c4)
                {
                  case '\n':
                    x1 = x2; break;
                  case '+':
                    switch(c5)
                    {
                      case '1':
                        x1 = x2 + x1; break;
                      case '2':
                        x1 = x2 + x2; break;
                      case '3':
                        x1 = x2 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':
                    switch(c5)
                    {
                      case '1':
                        x1 = x2 * x1; break;
                      case '2':
                        x1 = x2 * x2; break;
                      case '3':
                        x1 = x2 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':
                    switch(c5)
                    {
                      case '1':
                        x1 = x2 - x1; break;
                      case '2':
                        x1 = x2 - x2; break;
                      case '3':
                        x1 = x2 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 1=2
          
              case '3': // case '1=3'
                switch(c4)
                {
                  case '\n':
                    x1 = x3; break;
                  case '+':
                    switch(c5)
                    {
                      case '1':
                        x1 = x3 + x1; break;
                      case '2':
                        x1 = x3 + x2; break;
                      case '3':
                        x1 = x3 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':
                    switch(c5)
                    {
                      case '1':
                        x1 = x3 * x1; break;
                      case '2':
                        x1 = x3 * x2; break;
                      case '3':
                        x1 = x3 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':
                    switch(c5)
                    {
                      case '1':
                        x1 = x3 - x1; break;
                      case '2':
                        x1 = x3 - x2; break;
                      case '3':
                        x1 = x3 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 1=3

              case '=':  // case 1==
                switch(c4)
                {
                  case '1':
                    if (x1 == x1)
                      std::cout << "x1 == x1 is TRUE\n";
                    else
                      std::cout << "x1 == x1 is FALSE\n";
                    break;
                  case '2':
                    if (x1 == x2)
                      std::cout << "x1 == x2 is TRUE\n";
                    else
                      std::cout << "x1 == x2 is FALSE\n";
                    break;
                  case '3':
                    if (x1 == x3)
                      std::cout << "x1 == x3 is TRUE\n";
                    else
                      std::cout << "x1 == x3 is FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
                
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;  // end case 1=

            /* // begin set containment cases
          case '<':  // case 1<
            switch(c3)
            {
              case '=':
                switch(c4)
                {
                  case '1':
                    std::cout << "x1 <= x1 is ";
                    if (x1 <= x1) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '2':
                    std::cout << "x1 <= x2 is ";
                    if (x1 <= x2) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '3':
                    std::cout << "x1 <= x3 is ";
                    if (x1 <= x3) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              case '1':
                std::cout << "x1 < x1 is ";
                if (x1 < x1) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '2':
                std::cout << "x1 < x2 is ";
                if (x1 < x2) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '3':
                std::cout << "x1 < x3 is ";
                if (x1 < x3) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '>':  // case 1>
            switch(c3)
            {
              case '=':
                switch(c4)
                {
                  case '1':
                    std::cout << "x1 >= x1 is ";
                    if (x1 >= x1) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '2':
                    std::cout << "x1 >= x2 is ";
                    if (x1 >= x2) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '3':
                    std::cout << "x1 >= x3 is ";
                    if (x1 >= x3) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              case '1':
                std::cout << "x1 > x1 is ";
                if (x1 > x1) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '2':
                std::cout << "x1 > x2 is ";
                if (x1 > x2) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '3':
                std::cout << "x1 > x3 is ";
                if (x1 > x3) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
            // end set containment cases */
            
            // ***************************************************************** //
            //     1 += n, 1 -= n, 1 *= n                                        //
            // ***************************************************************** //

          case '+': // c2 = +
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x1 += x1;
                break;
              case '2':
                x1 += x2;
                break;
              case '3':
                x1 += x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '*': // c2 = *
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x1 *= x1;
                break;
              case '2':
                x1 *= x2;
                break;
              case '3':
                x1 *= x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '-': // c2 = -
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x1 -= x1;
                break;
              case '2':
                x1 -= x2;
                break;
              case '3':
                x1 -= x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;

            // ***************************************************************** //
            //     Insert, Remove, Member, Clear, Size, Empty, Dump, Display     //
            // ***************************************************************** //

          case '1':
            x1.Insert(t);
            break;

          case '2':
            x1.Remove(t);
            break;

          case 'f':
            if (x1.Member(t))
              std::cout << t << " is in x1\n";
            else
              std::cout << t << " is NOT in x1\n";
            break;
        
          case 'c':
            x1.Clear();
            break;
        
          case 's':
            std::cout << "x1.Size() == " << x1.Size() << '\n';
            break;
        
          case 'e':
            std::cout << "x1.Empty() == " << x1.Empty() << '\n';
            break;
        
          case 'r':  // Range()
            std::cout << " x1 universe = [0, " << x1.Range()<< ")\n";
            break;          
        
          case 'd':  // Dump()
            x1.Dump(std::cout);
            break;          
        
          case 'o':  // output
            std::cout << x1 << '\n';
            break;          
        
          default:
            std::cout << "Unrecognized command - please try again:\n";
            break;
            
        }  // end switch(c2)
      
        break; // case '1'

      case '2':
      // ************************************************************* //
      //     general case c1 = '2'
      // ************************************************************* //

        switch (c2)
        {

        // ***************************************************************** //
        //     2 = n, 2 = m op n  [ ops: +, *, -, <, <=, ==, !=, >=, > ]     //
        // ***************************************************************** //

          case '!':
            switch(c4)
            {
              case '1':
                if (x2 != x1)
                  std::cout << "x2 != x1 is TRUE\n";
                else
                  std::cout << "x2 != x1 is FALSE\n";
                break;
              case '2':
                if (x2 != x2)
                  std::cout << "x2 != x2 is TRUE\n";
                else
                  std::cout << "x2 != x2 is FALSE\n";
                break;
              case '3':
                if (x2 != x3)
                  std::cout << "x2 != x3 is TRUE\n";
                else
                  std::cout << "x2 != x3 is FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;        
            
          case '=':   // case 2=
            switch (c3)    
            {
              case '1': // case '2=1?'
                switch(c4)
                {
                  case '\n': // case '2=1'
                    x2 = x1; break;
                  case '+':  // case '2=1+?'
                    switch(c5)
                    {
                      case '1':
                        x2 = x1 + x1; break;
                      case '2':
                        x2 = x1 + x2; break;
                      case '3':
                        x2 = x1 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':  // case '2=1*?'
                    switch(c5)
                    {
                      case '1':
                        x2 = x1 * x1; break;
                      case '2':
                        x2 = x1 * x2; break;
                      case '3':
                        x2 = x1 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':  // case '2=1-?'
                    switch(c5)
                    {
                      case '1':
                        x2 = x1 - x1; break;
                      case '2':
                        x2 = x1 - x2; break;
                      case '3':
                        x2 = x1 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 2=1
                
              case '2': // case '2=2'
                switch(c4)
                {
                  case '\n':
                    x2 = x2; break;
                  case '+':
                    switch(c5)
                    {
                      case '1':
                        x2 = x2 + x1; break;
                      case '2':
                        x2 = x2 + x2; break;
                      case '3':
                        x2 = x2 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':
                    switch(c5)
                    {
                      case '1':
                        x2 = x2 * x1; break;
                      case '2':
                        x2 = x2 * x2; break;
                      case '3':
                        x2 = x2 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':
                    switch(c5)
                    {
                      case '1':
                        x2 = x2 - x1; break;
                      case '2':
                        x2 = x2 - x2; break;
                      case '3':
                        x2 = x2 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 2=2
                
              case '3': // case '2=3'
                switch(c4)
                {
                  case '\n':
                    x2 = x3; break;
                  case '+':
                    switch(c5)
                    {
                      case '1':
                        x2 = x3 + x1; break;
                      case '2':
                        x2 = x3 + x2; break;
                      case '3':
                        x2 = x3 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':
                    switch(c5)
                    {
                      case '1':
                        x2 = x3 * x1; break;
                      case '2':
                        x2 = x3 * x2; break;
                      case '3':
                        x2 = x3 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':
                    switch(c5)
                    {
                      case '1':
                        x2 = x3 - x1; break;
                      case '2':
                        x2 = x3 - x2; break;
                      case '3':
                        x2 = x3 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;

                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 2=3

              case '=':  // case 2==
                switch(c4)
                {
                  case '1':
                    if (x2 == x1)
                      std::cout << "x2 == x1 is TRUE\n";
                    else
                      std::cout << "x2 == x1 is FALSE\n";
                    break;
                  case '2':
                    if (x2 == x2)
                      std::cout << "x2 == x2 is TRUE\n";
                    else
                      std::cout << "x2 == x2 is FALSE\n";
                    break;
                  case '3':
                    if (x2 == x3)
                      std::cout << "x2 == x3 is TRUE\n";
                    else
                      std::cout << "x2 == x3 is FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
                
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;  // end case 2=

            /* // begin set containment cases
          case '<':  // case 2<
            switch(c3)
            {
              case '=':
                switch(c4)
                {
                  case '1':
                    std::cout << "x2 <= x1 is ";
                    if (x2 <= x1) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '2':
                    std::cout << "x2 <= x2 is ";
                    if (x2 <= x2) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '3':
                    std::cout << "x2 <= x3 is ";
                    if (x2 <= x3) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              case '1':
                std::cout << "x2 < x1 is ";
                if (x2 < x1) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '2':
                std::cout << "x2 < x2 is ";
                if (x2 < x2) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '3':
                std::cout << "x2 < x3 is ";
                if (x2 < x3) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '>':  // case 2>
            switch(c3)
            {
              case '=':
                switch(c4)
                {
                  case '1':
                    std::cout << "x2 >= x1 is ";
                    if (x2 >= x1) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '2':
                    std::cout << "x2 >= x2 is ";
                    if (x2 >= x2) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '3':
                    std::cout << "x2 >= x3 is ";
                    if (x2 >= x3) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              case '1':
                std::cout << "x2 > x1 is ";
                if (x2 > x1) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '2':
                std::cout << "x2 > x2 is ";
                if (x2 > x2) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '3':
                std::cout << "x2 > x3 is ";
                if (x2 > x3) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
            // end set containment cases */
        
            // ***************************************************************** //
            //     2 += n, 2 -= n, 2 *= n                                        //
            // ***************************************************************** //

          case '+': // c2 = +
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x2 += x1;
                break;
              case '2':
                x2 += x2;
                break;
              case '3':
                x2 += x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '*': // c2 = *
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x2 *= x1;
                break;
              case '2':
                x2 *= x2;
                break;
              case '3':
                x2 *= x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '-': // c2 = -
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x2 -= x1;
                break;
              case '2':
                x2 -= x2;
                break;
              case '3':
                x2 -= x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
            
            // ***************************************************************** //
            //     Insert, Remove, Member, Clear, Size, Empty, Dump, Display     //
            // ***************************************************************** //
            
          case '1':
            x2.Insert(t);
            break;
            
          case '2':
            x2.Remove(t);
            break;
            
          case 'f':
            if (x2.Member(t))
              std::cout << t << " is in x2\n";
            else
              std::cout << t << " is NOT in x2\n";
            break;
            
          case 'c':
            x2.Clear();
            break;
            
          case 's':
            std::cout << "x2.Size() == " << x2.Size() << '\n';
            break;
            
          case 'e':
            std::cout << "x2.Empty() == " << x2.Empty() << '\n';
            break;
            
          case 'r':  // Range()
            std::cout << " x2 universe = [0, " << x2.Range()<< ")\n";
            break;          
            
          case 'd':  // Dump()
            x2.Dump(std::cout);
            break;          
            
          case 'o':  // output
            std::cout << x2 << '\n';
            break;          
            
          default:
            std::cout << "Unrecognized command - please try again:\n";
            break;
            
        }  // end switch(c2)
        
        break; // case '2'


      case '3':
      // ************************************************************* //
      //     general case c1 = '3'
      // ************************************************************* //

        switch (c2)
        {
          // ***************************************************************** //
          //     3 = n, 3 = m op n  [ ops: +, *, -, <, <=, ==, !=, >=, > ]     //
          // ***************************************************************** //
        
          case '!':
            switch(c4)
            {
              case '1':
                if (x3 != x1)
                  std::cout << "x3 != x1 is TRUE\n";
                else
                  std::cout << "x3 != x1 is FALSE\n";
                break;
              case '2':
                if (x3 != x2)
                  std::cout << "x3 != x2 is TRUE\n";
                else
                  std::cout << "x3 != x2 is FALSE\n";
                break;
              case '3':
                if (x3 != x3)
                  std::cout << "x3 != x3 is TRUE\n";
                else
                  std::cout << "x3 != x3 is FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;        
          
          case '=':   // case 3=
            switch (c3)    
            {
              case '1': // case '3=1?'
                switch(c4)
                {
                  case '\n': // case '3=1'
                    x3 = x1; break;
                  case '+':  // case '3=1+?'
                    switch(c5)
                    {
                      case '1':
                        x3 = x1 + x1; break;
                      case '2':
                        x3 = x1 + x2; break;
                      case '3':
                        x3 = x1 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':  // case '3=1*?'
                    switch(c5)
                    {
                      case '1':
                        x3 = x1 * x1; break;
                      case '2':
                        x3 = x1 * x2; break;
                      case '3':
                        x3 = x1 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':  // case '3=1-?'
                    switch(c5)
                    {
                      case '1':
                        x3 = x1 - x1; break;
                      case '2':
                        x3 = x1 - x2; break;
                      case '3':
                        x3 = x1 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 3=1
              
              case '2': // case '3=2'
                switch(c4)
                {
                  case '\n':
                    x3 = x2; break;
                  case '+':
                    switch(c5)
                    {
                      case '1':
                        x3 = x2 + x1; break;
                      case '2':
                        x3 = x2 + x2; break;
                      case '3':
                        x3 = x2 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':
                    switch(c5)
                    {
                      case '1':
                        x3 = x2 * x1; break;
                      case '2':
                        x3 = x2 * x2; break;
                      case '3':
                        x3 = x2 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':
                    switch(c5)
                    {
                      case '1':
                        x3 = x2 - x1; break;
                      case '2':
                        x3 = x2 - x2; break;
                      case '3':
                        x3 = x2 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 3=2
                
              case '3': // case '3=3'
                switch(c4)
                {
                  case '\n':
                    x3 = x3; break;
                  case '+':
                    switch(c5)
                    {
                      case '1':
                        x3 = x3 + x1; break;
                      case '2':
                        x3 = x3 + x2; break;
                      case '3':
                        x3 = x3 + x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '*':
                    switch(c5)
                    {
                      case '1':
                        x3 = x3 * x1; break;
                      case '2':
                        x3 = x3 * x2; break;
                      case '3':
                        x3 = x3 * x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                  case '-':
                    switch(c5)
                    {
                      case '1':
                        x3 = x3 - x1; break;
                      case '2':
                        x3 = x3 - x2; break;
                      case '3':
                        x3 = x3 - x3; break;
                      default:
                        std::cout << "Unrecognized command - please try again:\n";
                    }
                    break;
                    
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;  // end case 3=3
                
              case '=':  // case 3==
                switch(c4)
                {
                  case '1':
                    if (x3 == x1)
                      std::cout << "x3 == x1 is TRUE\n";
                    else
                      std::cout << "x3 == x1 is FALSE\n";
                    break;
                  case '2':
                    if (x3 == x2)
                      std::cout << "x3 == x2 is TRUE\n";
                    else
                      std::cout << "x3 == x2 is FALSE\n";
                    break;
                  case '3':
                    if (x3 == x3)
                      std::cout << "x3 == x3 is TRUE\n";
                    else
                      std::cout << "x3 == x3 is FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;  // end case 3=

            /* // begin set containment cases
          case '<':  // case 3<
            switch(c3)
            {
              case '=':
                switch(c4)
                {
                  case '1':
                    std::cout << "x3 <= x1 is ";
                    if (x3 <= x1) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '2':
                    std::cout << "x3 <= x2 is ";
                    if (x3 <= x2) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '3':
                    std::cout << "x3 <= x3 is ";
                    if (x3 <= x3) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              case '1':
                std::cout << "x3 < x1 is ";
                if (x3 < x1) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '2':
                std::cout << "x3 < x2 is ";
                if (x3 < x2) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '3':
                std::cout << "x3 < x3 is ";
                if (x3 < x3) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '>':  // case 3>
            switch(c3)
            {
              case '=':
                switch(c4)
                {
                  case '1':
                    std::cout << "x3 >= x1 is ";
                    if (x3 >= x1) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '2':
                    std::cout << "x3 >= x2 is ";
                    if (x3 >= x2) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  case '3':
                    std::cout << "x3 >= x3 is ";
                    if (x3 >= x3) std::cout << "TRUE\n";
                    else std::cout << "FALSE\n";
                    break;
                  default:
                    std::cout << "Unrecognized command - please try again:\n";
                }
                break;
              case '1':
                std::cout << "x3 > x1 is ";
                if (x3 > x1) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '2':
                std::cout << "x3 > x2 is ";
                if (x3 > x2) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              case '3':
                std::cout << "x3 > x3 is ";
                if (x3 > x3) std::cout << "TRUE\n";
                else std::cout << "FALSE\n";
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
            // end set containment cases */
        
            // ***************************************************************** //
            //     3 += n, 3 -= n, 3 *= n                                        //
            // ***************************************************************** //

          case '+': // c2 = +
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x3 += x1;
                break;
              case '2':
                x3 += x2;
                break;
              case '3':
                x3 += x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '*': // c2 = *
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x3 *= x1;
                break;
              case '2':
                x3 *= x2;
                break;
              case '3':
                x3 *= x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
          case '-': // c2 = -
            if (c3 != '=')
            {
              std::cout << "Unrecognized command - please try again:\n";
            }
            switch(c4)
            {
              case '1':
                x3 -= x1;
                break;
              case '2':
                x3 -= x2;
                break;
              case '3':
                x3 -= x3;
                break;
              default:
                std::cout << "Unrecognized command - please try again:\n";
            }
            break;
            
            // ***************************************************************** //
            //     Insert, Remove, Member, Clear, Size, Empty, Dump, Display     //
            // ***************************************************************** //

          case '1':
            x3.Insert(t);
            break;
            
          case '2':
            x3.Remove(t);
            break;
            
          case 'f':
            if (x3.Member(t))
              std::cout << t << " is in x3\n";
            else
              std::cout << t << " is NOT in x3\n";
            break;
            
          case 'c':
            x3.Clear();
            break;
            
          case 's':
            std::cout << "x3.Size() == " << x3.Size() << '\n';
            break;
            
          case 'e':
            std::cout << "x3.Empty() == " << x3.Empty() << '\n';
            break;
            
          case 'r':  // Range()
            std::cout << " x3 universe = [0, " << x3.Range()<< ")\n";
            break;          
            
          case 'd':  // Dump()
            x3.Dump(std::cout);
            break;          
            
          case 'o':  // output
            std::cout << x3 << '\n';
            break;          
            
          default:
            std::cout << "Unrecognized command - please try again:\n";
            break;
            
        }  // end switch(c2)
        
        break; // case '3'

        // ************************************************************* //
        //     universal commands                                        //
        // ************************************************************* //

      case '=':
        x3 = x2 = x1;
        break;

      case 'm': case 'M':
        DisplayMenu();
        break;

      case 'x': case 'X':
        if (BATCH)
        {
          isptr = &std::cin;
          ifs.close();
          BATCH = 0;
          std::cout << " ** switched to interactive mode\n";
        }
        else
        {
          std::cout << " ** already in interactive mode\n";
        }
        break;
      case 'q': case 'Q':
        if (BATCH)
        {
          ifs.close();
        }
        break;
        
      default:
        std::cout << "Unrecognized command - please try again:\n";
        do c1 = isptr->get();
        while (c1 != '\n');
        
    }  // end switch(c1)
    
  }  // end do
  while (c1 != 'q');
  
  std::cout << "\nHave a nice day." << std::endl;
  return EXIT_SUCCESS;
}  // end main()

void Preamble()
{
  std::cout << "  ----------------------------------------------------------------\n"
            << "  Welcome to fuintset - functionality interface to the UIntSet API\n"
            << "  Three UIntSet objects s1 s2 s3 are created, with upper bound the\n"
            << "  required command line argument. To operate the interface, indicate\n"
            << "  which set set to be called with a number [1, 2, or 3] followed by\n"
            << "  the command and any argument required for the command.\n"
            << "  Examples:\n"
            << '\n'
            << "    enter this        to make this happen\n"
            << "    ----------        -------------------\n"
            << "    213               s2.Insert(3)\n"
            << "    1+=2              s1 += s2\n"
            << "    3O                std::cout << s3\n"
            << "    2D                s2.Dump(std::cout)\n"
            << "    2=1*3             s2 = s1 * s3\n"
            << "    =                 s1 = s2 = s3\n"
            << '\n'
            << "  Enjoy!\n";
}

void DisplayMenu()
{
  std::cout << "  ------------------------------------------------------------\n"
            << "  OPERATION                                            COMMAND\n"
            << "  ---------                                            -------\n"
            << "  binary operators + , * , -  .......................  [set]=[set][op][set]\n"
            << "  relational operators == , !=  .....................  [set][op][set]\n"
    // << "  relational operators == , != , < , <= , > , >= ....  [set][op][set]\n"
            << "  unary operators += , *= , -= ......................  [set][op][set]\n"
            << "  assignment ........................................  [set]=[set]\n"
            << "  3-way assignment s3 = s2 = s1  ....................  =\n"
            << '\n'
            << "  Insert       (val)  ...............................  [set]1[val]\n"
            << "  Remove       (val)  ...............................  [set]2[val]\n"
            << "  Member       (val)  ...............................  [set]F[val]\n"
            << '\n'
            << "  Empty        ()  ..................................  [set]E\n"
            << "  Size         ()  ..................................  [set]S\n"
            << "  Clear        ()  ..................................  [set]C\n"
            << "  Range        ()  ..................................  [set]R\n"
            << "  Dump         ()  ..................................  [set]D\n"
            << "  std::cout << s?  ..................................  [set]O\n"
            << "  switch to interactive mode  .......................  X\n"
            << "  display Menu  .....................................  M\n\n";
} // void DisplayMenu()

void GetCommands
  (
    char& c1, char& c2, char& c3, char& c4, char& c5,  // command characters (5 deep)
    unsigned long& t, unsigned long upperbound,        // command arguments
    std::istream* p, bool BATCH                        // input control
  )
{
  // get commands block
  // we want to leave future commands in the input stream when possible
  {
    bool finished = 0;
    c1 = c2 = c3 = c4 = c5 = '\n';
    *p >> c1;
    c1 = tolower(c1);
    if (c1 == '=' || c1 == 'm' || c1 == 'f' || c1 == 'q'|| c1 == 'x')
    // single commands
    {
      if (BATCH) std::cout << c1 << '\n';
      finished = 1;
    }
    else 
    {
      p->get(c2);
      c2 = tolower(c2);
    }
    if (!finished)
    // 2 or more
    {
      if (c2 == 'c' || c2 == 'd' || c2 == 'o' || c2 == 'e' || c2 == 'r' || c2 == 's' || c2 == 't')
      // exactly 2
      {
	if (BATCH) std::cout << c1 << c2 << '\n';
	finished = 1;
      }
      else if (c2 == 'i' || c2 == '1' || c2 == 'r' || c2 == '2'
	                 || c2 == 'l' || c2 == 'u' || c2 == 'f')
      // 2 + argument
      {
	*p >> t;
	if (BATCH) std::cout << c1 << c2 << t << '\n';
	if (t >= upperbound)
	{
	  std::cout << " ** Element too large - converting to remainder: ";
	  t = t % upperbound;
	  std::cout << t << '\n';
	}
	finished = 1;
      }
      else
      // 3 or more - here we assume user has entered a single command consting
      // of 3, 4, or 5 characters
      {
	p->get(c3);
	p->get(c4);
	if (BATCH) std::cout << c1 << c2 << c3 << c4;
	if (c4 != '\n')
	{
	  p->get(c5);
	  if (BATCH) std::cout << c5 << '\n';
	}
	finished = 1;
      }
    }
  }
} // get commands

void BadCommand(std::istream* p)
{
  std::cout << "Unrecognized command - please try again:\n";
  char c;
  do c = p->get();
  while (!(p->fail()) && c!= '\0');
  p->clear();
}


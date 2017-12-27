/*
     main.cpp
     01-21-15

     driver program for WordSmith
*/

#include <wordsmith.h>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <fstream>

void  DisplayMenu ();

int main( int argc, char* argv[] )
{
  bool BATCH = 0;
  if (argc > 1) BATCH = 1;
  std::istream* isptr = &std::cin;
  std::ifstream comstream;
  if (BATCH)
  {
    comstream.open(argv[1]);
    if (comstream.fail())
    {
      std::cout << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    isptr = &comstream;
  }
  std::cout << "Welcome to WordSmith, a Text Analysis Utility.\n";
  if (!BATCH) DisplayMenu();

  WordSmith ws;
  char selection;
  fsu::String filename;
  fsu::String last_report;
  std::ifstream ifs;
  do
  {
    std::cout <<   "\nWS command ('m' for menu, 'q' to exit): ";
    *isptr >> selection;
    if (BATCH) std::cout << selection << '\n';
    switch (selection)
    {
      case 'r': case 'R':
        std::cout << "  Enter file name : ";
        *isptr >> filename;
        if (BATCH) std::cout << filename << '\n';
        while (!ws.ReadText(filename,0))
        {
          std::cout << "    ** Cannot open file " << filename << '\n'
                    << "    Try another file name: ";
          *isptr >> filename;
          if (BATCH) std::cout << filename << '\n';
        }
        break;
       
      case 'p':  case 'P':
        std::cout << "  Enter file name : ";
        *isptr >> filename;
        if (BATCH) std::cout << filename << '\n';
        while (!ws.ReadText(filename,1))
        {
          std::cout << "    ** Cannot open file " << filename << '\n'
                    << "    Try another file name: ";
          *isptr >> filename;
          if (BATCH) std::cout << filename << '\n';
        }
        break;
       
      case 'w': case 'W': 
        std::cout << "  Enter file name: ";
        *isptr >> filename;
        if (BATCH) std::cout << filename << '\n';
        while (!ws.WriteReport(filename))
        {
          std::cout << "    ** Cannot open file " << filename << '\n'
                    << "    Try another file name: ";
          *isptr >> filename;
          if (BATCH) std::cout << filename << '\n';
        }
        last_report = filename;
        break;

      case 'f': case 'F':
        if (last_report.Size() == 0)
        {
          std::cout << "    ** Last report name is null\n";
          break;
        }
        ifs.open(last_report.Cstr());
        if (ifs.fail())
        {
          std::cout << "    ** Cannot open file " << last_report << '\n';
          break;
        }
        char ch;
        while(ifs.get(ch))
          std::cout.put(ch);
        ifs.close();
        ifs.clear();
        break;

      case 'c': case 'C':
        ws.ClearData();
        std::cout << "\n     Current data erased\n";
        break;

      case 's': case 'S':
        ws.ShowSummary();
        break;
     
      case 'm': case 'M':
        DisplayMenu();
        break;

      case 'x': case 'X':
        if (BATCH)
        {
          std::cout << "  switching to interactive mode\n";
          isptr = &std::cin;
          comstream.close();
          comstream.clear();
          BATCH = 0;
          DisplayMenu();
        }
        else
        {
          std::cout << "  already in interactive mode\n";
        }
        break;
     
      case 'q':  case 'Q':
        if (BATCH)
          ifs.close();
        selection = 'q';
        break;
     
      default:
        std::cout << "\n     ** Command not found -- try again\n";
    }
  }
  while (selection != 'q');

  std::cout << "\nWordSmith wishes you a nice day." << std::endl;
  return EXIT_SUCCESS;
}  // end main()

void DisplayMenu()
{
  std::cout << '\n'
            << "     WS Command                              key\n"
            << "     ----------                              ---\n"
            << "     Read a file  .........................  'R'\n"
            << "     read a file showing Progress .........  'P'\n"
            << "     show Summary  ........................  'S'\n"
            << "     Write report  ........................  'W'\n"
            << "     show last report File to screen ......  'F'\n"
            << "     Clear current data  ..................  'C'\n"
            << "     eXit BATCH mode  .....................  'X'\n"
            << "     display Menu  ........................  'M'\n"
            << "     Quit program  ........................  'Q'\n";
}

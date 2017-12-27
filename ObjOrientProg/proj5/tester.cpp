/*
   tester.cpp

   Chris Lacher
   10-10-14

   Test harness for the vehicle object hierarchy

   VehicleType is an enumerated type with values:

     badSn, vehicle, car, truck, van, tanker, flatbed

   These classes are tested:

     Vehicle;
     Car;
     Truck;
     Van;
     Tanker;
     Flatbed;
     Box;
     Cylinder;
     Plane;
*/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <vehicles.h>

char  snMessage  [54] = "*** OOPS - serial number not owned by vehicle object";
char  dotMessage [55] = "*** OOPS - license number not owned by vehicle object";
char  dotLicense [15] = "DOTLICENSE OK";
const size_t maxEntrySize(1+strlen(dotMessage));

int main(int argc, char* argv[])
{
  bool BATCH = 0;
  std::istream * isptr = &std::cin;
  std::ifstream ifs;
  if (argc > 1)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cout << " ** cannot open command file " << argv[1] << '\n';
      exit (EXIT_FAILURE);
    }
    isptr = &ifs;
    BATCH = 1;
  }

  Vehicle *   Vptr;              // pointer to dynamically allocated Vehicle object
  VehicleType v;                 // to hold type of vehicle
  char        sn [maxEntrySize]; // to hold user entry
  char        dot[maxEntrySize]; // used to test ownership of DOT License number
  std::cout << std::fixed << std::showpoint << std:: setprecision(2); // set float output format

  do
  {
    std::cout << "\nEnter sn ('x' to quit): ";
    (*isptr) >> std::setw(maxEntrySize) >> sn;
    if (BATCH) std::cout << sn << '\n';
    if (sn[0] == 'x') break;
    v = Vehicle::SnDecode(sn);
    switch (v)
    {
      case vehicle:
        Vptr = new Vehicle(sn, 1, 1);
        break;
      case car:
        Vptr = new Car(sn, 2, 1);
        break;
      case truck:
        strcpy (dot,dotLicense);
        Vptr = new Truck(sn, 3, dot, 1);
        break;
      case van:
        strcpy (dot,dotLicense);
        Vptr = new Van(sn, 4, dot, 20, 4, 8, 1);
        break;
      case tanker:
        strcpy (dot,dotLicense);
        Vptr = new Tanker(sn, 5, dot, 40, 3, 1);
        break;
      case flatbed:
        strcpy (dot,dotLicense);
        Vptr = new Flatbed(sn, 6, dot, 20, 6, 1);
        break;
      case badSn:
        Vptr = new Vehicle ("BadSerialNumber",0, 1);
        break;
      default:  // should never get here
        std::cerr << "** ERROR: bad serial number passed to decision logic\n";
        break;
    } // end switch

    strcpy (sn, snMessage);
    strcpy (dot, dotMessage);
    std::cout << "Short Name:    " << Vptr -> ShortName() << '\n';
    std::cout << "Toll Charge:   " << Vptr -> Toll() << '\n';
    std::cout << "Serial Number: " << Vptr -> SerialNumber() << '\n';
    std::cout << "Passenger Cap: " << Vptr -> PassengerCapacity() << '\n';
    std::cout << "Load Capacity: " << Vptr -> LoadCapacity() << '\n';
    if ( truck <= v ) // all types of trucks
    { 
      std::cout << "DOT License:   " << (dynamic_cast<Truck*>(Vptr)) -> DOTLicense() << '\n';
    }

    delete Vptr;
  } // end do
  while (sn[0] != '0');

  return 0;
} // end main

/*
tracker.cpp
October 21st, 2015
Blake Kershaw
kershaw
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#include <vehicles.h>

const unsigned int
C1 = 6,  //short name
C2 = 7,  //toll
C3 = 10, //pass cap
C4 = 10, //load cap
c5 = 2,  //C5 += c5 - dot license
c6 = 2,  //C6 += c6 - serial number
maxSegmentSize = 100,
maxSerialNumber = 50,
maxDotLicense = 50;

unsigned int
A0 = 5,  // Car setwidth
A1 = 3,  // Truck
A2 = 5,  // Van
A3 = 2,  // Tanker
A4 = 0,  // Flatbed
A7 = 0,  // Vehicle
A8 = 4,  // Badsn
A5 = 5,  // tonnage
A6 = 3,  // tolls
C5 = 11, // Dot License
C6 = 13; // Serial Number



void Output(Vehicle *);

int main()
{

C5 += c5;
C6 += c6;

char         sn[maxSerialNumber]; //char array of max serial number characters
char         dot[maxDotLicense]; //char array of max dot characters
size_t       segSize;

Vehicle *segment[maxSegmentSize];
VehicleType v;

std::cout <<"\nRCL::Tracker started...\n"; //Program initatied

do
{
size_t pc;
float  d1;
float  d2;
float  d3;
float  tonnage = 0.00;
float  tolls = 0.00;
int    badSnTotal = 0;
int    vehicleTotal = 0;
int    carTotal = 0;
int    truckTotal = 0;
int    vanTotal = 0;
int    tankerTotal = 0;
int    flatbedTotal = 0;

std::cin >> segSize;
if (segSize == 0)
  break;
if (segSize > maxSegmentSize)
{
  std::cerr << "Error\n";
  break;
}

for(size_t i = 0; i < segSize; ++i)
{
  std::cin >> sn;
  v = Vehicle::SnDecode(sn);
switch(v)
{
case badSn:
  ++badSnTotal;
  std::cin >> pc;
  segment[i] = new Vehicle(sn, pc, false);
  break;
case vehicle:
  ++vehicleTotal;
  std::cin >> pc;
  segment[i] = new Vehicle(sn, pc, false);
  break;
case car:
  ++carTotal;
  std::cin >> pc;
  segment[i] = new Car(sn, pc, false);
  break;
case truck:
  ++truckTotal;
  std::cin >> pc >> dot;
  segment[i] = new Truck(sn, pc, dot, false);
  break;
case van:
  ++vanTotal;
  std::cin >> pc >> dot >> d1 >> d2 >> d3;
  segment[i] =  new Van(sn, pc, dot, d1, d2, d3, false);
  break;
case tanker:
  ++tankerTotal;
  std::cin >> pc >> dot >> d1 >> d2;
  segment[i] = new Tanker(sn, pc, dot, d1, d2, false);
  break;
case flatbed:
  ++flatbedTotal;
  std::cin >> pc >> dot >> d1 >> d2;
  segment[i] = new Flatbed(sn, pc, dot, d1, d2, false);
  break;
default:
 std::cerr << "Error bad SerialNumber\n";
 break;
} //end switch

if (segment[i] == 0)
{
  std::cerr << "Error Memory problem\n";
  break;
}

tonnage += segment[i] -> LoadCapacity();
tolls += segment[i] -> Toll();



if(strlen(dot) > 13)
  C5 = strlen(dot) + 2;

if(strlen(sn) > 15)
  C6 = strlen(sn) + 2;


} //end for loop

// setw for object outputs
if (carTotal > 9)
  A0 = 6;
if (truckTotal > 9)
  A1 = 4;
if (vanTotal > 9)
  A2 = 6;
if (tankerTotal > 9)
  A3 = 3;
if (flatbedTotal > 9)
  A4 = 1;
if (vehicleTotal > 9)
  A7 = 1;
if (badSnTotal > 9)
  A8 = 5;

// setw for tonnage output
if (tonnage > 9)
  A5 = 6;

if (tonnage > 99)
  A5 = 7;

if (tonnage >  999)
  A5 = 8;

if (tonnage > 9999)
  A5 = 9;
// setw for tolls output

if (tolls > 9)
  A6 = 4;
if (tolls > 99)
  A6 = 5;
if (tolls > 999)
  A6 = 6;

std::cout << "\nSegment Summary\n===============\n";
std::cout << "\n  Cars: " << std::setw(A0) << carTotal;
std::cout << "\n  Trucks: " << std::setw(A1) << truckTotal;
std::cout << "\n  Vans: " << std::setw(A2) << vanTotal;
std::cout << "\n  Tankers: " << std::setw(A3) << tankerTotal;
std::cout << "\n  Flatbeds: " << std::setw(A4) << flatbedTotal;
std::cout << "\n  Unknowns: " << std::setw(A7) << vehicleTotal;
std::cout << "\n  Badsn: " << std::setw(A8) << badSnTotal;
std::cout << std::setprecision(2) << std::fixed;
std::cout << "\n  Tonnage: " << std::setw(A5) << tonnage;
std::cout << "\n  Tolls: " << "   $" << std::setw(A6) <<tolls;

std::cout << "\n\nSegment Details\n===============\n\n";
std::cout << std::setw(C1) << std::right <<
"Type" << std::setw(C2) <<
"Toll" << std::setw(C3) <<
"Pass Cap" << std::setw(C4) <<
"Load Cap" << std::setw(C5) <<
"DOT License" << std::setw(C6) <<
"Serial Number" << std::endl;

std::cout << std::setw(C1) << std::right <<
"----" << std::setw(C2) <<
"----" << std::setw(C3) <<
"--------" << std::setw(C4) <<
"--------" << std::setw(C5) <<
"-----------" << std::setw(C6) <<
"-------------" << std::endl;

for(size_t i = 0; i < segSize; ++i)
{
Output(segment[i]);
delete segment[i];
tonnage = 0;
tolls = 0;
} //end for loop
C5 = 13;
C6 = 15;
} //end do-while loop
while (segSize > 0);
  std::cout << "\n\n...Thank you for using SunPass Tracker.\n\n";

} //end main


void Output(Vehicle *v)
{
std::cout << std::setw(6) << std::setprecision(2) << std::fixed << std::right
<< std::showpoint << v->ShortName() << std::setw(7) << v->Toll()
<< std::setw(10) << v->PassengerCapacity() << std::setw(10)
<< v->LoadCapacity();
if (truck <= Vehicle::SnDecode( v-> SerialNumber() ) )
{
std::cout << std::setw(C5) << (dynamic_cast<Truck*>(v))->DOTLicense();
}
else
std::cout << std::setw(C5) << "(NA)";
std::cout << std::setw(C6) << v->SerialNumber()
<< std::endl;
}
 

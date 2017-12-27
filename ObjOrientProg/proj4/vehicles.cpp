/*
shapes.h
October 13th, 2015
Blake Kershaw
kershaw
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vehicles.h>
#include <shapes.h>



//~~~~~~~~~~VEHICLE~~~~~~~

Vehicle::Vehicle() :
  serialNumber_(0), passengerCapacity_(0),verbose_(0)
{
  if (Vehicle::verbose_)
    std::cout << "Vehicle()\n";
}

Vehicle::Vehicle(const char* sn, unsigned int pc, bool v) :
  serialNumber_(0), passengerCapacity_(pc), verbose_(v)
{
    serialNumber_ = new (std::nothrow) char [1 + strlen (sn)];
  if (serialNumber_ == 0)
  {
     std::cerr << "Unable to set memory for Vehicle serialNumber\n";
     exit (EXIT_FAILURE);
  }
  strcpy (serialNumber_, sn);
  if (Vehicle::verbose_)
    std::cout << "Vehicle()\n";
}

Vehicle::~Vehicle()
{
  delete [] serialNumber_;
  if (Vehicle::verbose_)
    std::cout << "~Vehicle()\n";
}

const char* Vehicle::SerialNumber() const
{
  return serialNumber_;
}

unsigned int Vehicle::PassengerCapacity() const
{
  return passengerCapacity_;
}

float Vehicle::LoadCapacity() const
{
  return 0.0;
}

const char* Vehicle::ShortName() const
{
  return "UNK";
}

float Vehicle::Toll() const
{
  return 2.00; //Not a Truck so return $2.00
}

VehicleType Vehicle::SnDecode(const char* sn)
{
  switch (sn[0])
  {
    case '1' : return vehicle;
    case '2' : return car;
    case '3' : return truck;
    case '4' : return van;
    case '5' : return tanker;
    case '6' : return flatbed;
    default  : return badSn;
  } //end switch
} // end VehicleType

//~~~~~~~CAR~~~~~~~

Car::Car() :
  Vehicle()
{
  if (Vehicle::verbose_)
    std::cout << "Car()\n";
}

Car::Car(const char* sn, unsigned int pc, bool v): Vehicle(sn, pc, v)
{
  if (Vehicle::verbose_)
    std::cout << "Car()\n";
}

Car::~Car()
{
  if (Vehicle::verbose_)
    std::cout << "~Car()\n";
}

const char* Car::ShortName() const
{
  return "CAR";
}

//~~~~~~~~TRUCK~~~~~~~

Truck::Truck() :
  Vehicle(), DOTLicense_(0)
{
  if (Vehicle::verbose_)
    std::cout << "Truck()\n";
}

Truck::Truck(const char* sn, unsigned int pc, const char* d, bool v): Vehicle(sn, pc, v), DOTLicense_(0)
{
  DOTLicense_ = new (std::nothrow) char [1 + strlen (d)];
  if (DOTLicense_ == 0)
  {
     std::cerr << "Unable to set memory for Truck DotLicense\n";
     exit (EXIT_FAILURE);
  }
  strcpy (DOTLicense_, d);
  if (Vehicle::verbose_)
    std::cout << "Truck()\n";
}

Truck::~Truck()
{
  delete[] DOTLicense_;
  if (Vehicle::verbose_)
    std::cout << "~Truck()\n";
}

const char* Truck::ShortName() const
{
  return "TRK";
}

float Truck::Toll() const
{
  return 10.00; //truck toll
}

const char* Truck::DOTLicense() const
{
  return DOTLicense_;
}

float Truck::LoadCapacity () const
{
  return Vehicle::LoadCapacity();
}

//~~~~~~~VAN~~~~~~~

Van::Van() : Truck(), Box()
{
  if (Vehicle::verbose_)
    std::cout << "Van()\n";
}

Van::Van(const char* sn, unsigned int pc, const char* d, float length, float width, float height, bool v) :
  Truck(sn, pc, d, v), Box (length, width, height, v)
{
  if (Vehicle::verbose_)
    std::cout << "Van()\n";
}

Van::~Van()
{
  if (Vehicle::verbose_)
    std::cout << "~Van()\n";
}

float Van::LoadCapacity() const 
{
  return Box::Volume();
}

const char* Van::ShortName() const
{
  return "VAN";
}

//~~~~~~~TANKER~~~~~~~
Tanker::Tanker() :
  Truck(), Cylinder()
{
  if (Vehicle::verbose_)
    std::cout << "Tanker()\n";
}

Tanker::Tanker(const char* sn, unsigned int pc, const char* d, float length, float radius, bool v) :
  Truck(sn, pc, d, v), Cylinder(length, radius, v)
{
  if (Vehicle::verbose_)
    std::cout << "Tanker()\n";
}

Tanker::~Tanker()
{
  if (Vehicle::verbose_)
    std::cout << "~Tanker()\n";
}

float Tanker::LoadCapacity() const
{
  return Cylinder::Volume();
}

const char* Tanker::ShortName() const
{
  return "TNK";
}

//~~~~~~FLATBED~~~~~~

Flatbed::Flatbed(): Truck(), Plane()
{
  if (Vehicle::verbose_)
    std::cout << "Flatbed()\n";
}

Flatbed::Flatbed(const char* sn, unsigned int pc, const char* d, float length, float width, bool v):
  Truck(sn, pc, d, v), Plane(length, width, v)
{
  if (Vehicle::verbose_)
    std::cout << "Flatbed()\n";
}

Flatbed::~Flatbed()
{
  if (Vehicle::verbose_)
    std::cout << "~Flatbed()\n";
}

float Flatbed::LoadCapacity() const
{
  return Plane::Area();
}

const char* Flatbed::ShortName() const
{
  return "FLT";
}


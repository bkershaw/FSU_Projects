/*
shapes.h
October 13th, 2015
Blake Kershaw
kershaw
*/

#ifndef VEHICLES_H_
#define VEHICLES_H_

#include <shapes.h>

enum VehicleType { badSn, vehicle, car, truck, van, tanker, flatbed };

class Vehicle 
{
public:
  Vehicle          ();
  Vehicle          (const char*, unsigned int, bool );
  virtual ~Vehicle ();

  const            char* SerialNumber        () const; // returns serial number
  virtual unsigned int   PassengerCapacity   () const; // returns passenger capacity
  virtual float          LoadCapacity        () const; // returns 0
  virtual const    char* ShortName           () const; // returns "UNK"
  virtual float          Toll                () const; // returns toll using fee schedule
  static         VehicleType SnDecode(const char* sn);
private:
  Vehicle            ( const Vehicle& );   //copy constructor
  Vehicle& operator= ( const Vehicle& t ); //assignment constructor

  char*        serialNumber_;
  unsigned int passengerCapacity_;
protected:
  bool verbose_;;
};

class Car: public Vehicle
{
public:
  Car         ();
  Car         ( const char*, unsigned int, bool );
  virtual ~Car();

 virtual const char* ShortName () const; //returns "CAR"
private:
  Car            ( const Car& );   //copy constructor
  Car& operator= ( const Car& c ); //assigment constructor

};

class Truck: public Vehicle
{
public:
  Truck          ();
  Truck          ( const char*, unsigned int, const char *, bool );
  virtual ~Truck ();

  virtual const char* ShortName  ()  const;  // returns "TRK"
  virtual float       Toll       ()  const;  // returns toll using fee schedule
  virtual const char* DOTLicense ()  const;  // returns the license no
  virtual float       LoadCapacity() const;
private:
  char* DOTLicense_;

  Truck            ( const Truck& );   //copy constructor
  Truck& operator= ( const Truck& t ); //assignment constructor
};
class Van: public Truck, Box
{
public:
  Van          ();
  Van          ( const char *, unsigned int, const char*, float, float, float, bool );
  virtual ~Van ();

  virtual float       LoadCapacity () const; //returns volume of box
  virtual const char* ShortName    () const; //returns "VAN"
private:
  Van            ( const Van& );   //copy constructor
  Van& operator= ( const Van& v ); //assignment constructor
};

class Tanker: public Truck, Cylinder
{
public:
  Tanker          ();
  Tanker          ( const char*, unsigned int, const char*, float, float, bool );
  virtual ~Tanker ();

  virtual float       LoadCapacity() const; //returns volume of cylinder
  virtual const char* ShortName   () const; //returns "TNK"
private:
  Tanker            ( const Tanker& );   //copy constructor
  Tanker& operator= ( const Tanker& a ); //assignment constructor

};
class Flatbed: public Truck, Plane
{
public:
  Flatbed          ();
  Flatbed          ( const char*, unsigned int, const char*, float, float, bool );
  virtual ~Flatbed ();

  virtual float       LoadCapacity () const; //returns area of plane
  virtual const char* ShortName    () const; //returns "FLT"
private:
  Flatbed            ( const Flatbed& );   //copy constructor
  Flatbed& operator= ( const Flatbed& f ); //assignment constuctor
};
#endif /* VEHICLES_H_ */

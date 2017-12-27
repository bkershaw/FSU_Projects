/*
    machine.h
    Decker & Hirschfield
    circa 1995

    modified recently by Chris Lacher

    This file contains the declaration of the "machine" classes SodaMachine,
    CoinCounter, and CanDispenser, as well as the "person" class ServicePerson.

    A SodaMachine object is a manager that contains one CoinCounter object and
    five CanDispenser objects (one for each brand of soda), along with the price
    of a can of soda.

A coin_counter object keeps track of money before, during, and after a
customer attempts to buy a can of soda.

A CanDispenser object keeps track of the cans of soda (of one brand)
and dispenses them on command, when it is not sold out.

A ServicePerson object is a friend of all of these classes and
reports private financial and inventory data.

NOTE: The soda machine simulation is based on ideas from "The Object
Concept" by Rick Decker and Stuart Hirshfield, PWS, Boston, 1995.
This is a fun book that we recommend for outside reading to students
after taking a first course in C or C++.

*/

#ifndef _MACHINE_H
#define _MACHINE_H

const int defaultSodaPrice       = 75;   // price of one soda in cents
const int defaultMachineBankroll = 100;  // default change amount in cents
const int defaultDispenserSize   = 24;   // default dispenser size

class CoinCounter
{
friend class ServicePerson;

public:
  CoinCounter(int machineBankroll_ = defaultMachineBankroll);
  // constructor
  // initialize a counter, setting available change
  // default parameters are constants at top of this file

  void AcceptCoin(int amt);
  // accept a coin input by user

  int CurrentAmount();
  // report amount tendered so far during a transaction

  void TakeAll();
  // accept all coins in response to a sale

  void DispenseChange(int amt);
  // return change, if possible

private:
  int amountTendered_; // the amount tendered during a transaction
  int inBank_;         // the amount available for making change
}  ;

class CanDispenser
{
friend class ServicePerson;

public:
  CanDispenser(int dispenserSize_ = defaultDispenserSize);
  // constructor
  // initialize a dispenser with number of cans = dispenser_size
  // default parameters are constants at top of this file

  bool SaleAttempt();
  // try to make a sale

private:
  int numCans_;   // the number of cans available
}  ;

class SodaMachine
{
friend class ServicePerson;

public:
  SodaMachine(int sodaPrice_ = defaultSodaPrice);
  // constructor
  // initialize a machine
  // default parameters are constants at top of this file

  void DoCommand(char cmd);
  // respond to a command from a customer

private:
  // a soda machine consists of:
  // -- one coin counter
  CoinCounter counter_;

  // -- five can dispensers
  CanDispenser cola_, lite_, root_, orng_, free_;

  // -- and the price of a can of soda.
  int price_;

  // a soda machine must manage
  // -- drink selection 
  void DoSelection(char cmd);

  // -- and coin events
  void DoCoin(char cmd);
}  ;

class ServicePerson
{
public:
  ServicePerson();
  // constructor 
  // sets cout for display of floats as money

  void Inventory(SodaMachine);
  // displays current amount of money and drinks in machine

private:
  int Money(CoinCounter);
  // returns amount of money in CoinCounter

  int Sodas(CanDispenser);
  // returns number of drinks in CanDispenser
}  ;

#endif


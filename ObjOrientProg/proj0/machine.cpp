/*
  file: machine.cpp

  This file contains implementations of member functions for the classes
  CoinCounter, CanDispenser, SodaMachine, and ServicePerson.

  NOTE: The soda machine simulation is based on ideas from "The Object
  Concept" by Rick Decker and Stuart Hirshfield, PWS, Boston, 1995.
  This is a fun book that we recommend for outside reading to students
  after taking COP 2000.  (This is the text for our class "Object
  Oriented Programming in C++" for non-majors.  CS majors cannot receive
  credit for this class.)  The book is available in the FSU book store.

*/

#include <iostream>
#include <machine.h>

/*-----------------------------------------------------------------*/
/* implementations of CoinCounter member functions                */
/*-----------------------------------------------------------------*/

CoinCounter::CoinCounter(int machineBankroll) :    amountTendered_(0), inBank_(machineBankroll)
// initialize a counter, setting available change
{}

int CoinCounter::CurrentAmount()
// report amount tendered so far
{
  return amountTendered_;
} // end CoinCounter::CurrentAmount()

void CoinCounter::AcceptCoin(int amt)
// handle coin insertion
{
  amountTendered_ += amt;
  return;
} // end CoinCounter::AcceptCoin()

void CoinCounter::TakeAll()
// respond to a sale by taking in all coins so far tendered
{
  inBank_ += amountTendered_;
  amountTendered_ = 0;
  return;
} // end CoinCounter::TakeAll()

void CoinCounter::DispenseChange(int amt)
// return change, if possible
{
  if (inBank_ >= amt)
  {
    std::cout << "*** CHANGE RETURNED: " << amt << " cents\n";
    inBank_ -= amt;
  }  // end if
  else
    std::cout << "*** EXACT CHANGE ONLY from now on\n";
  return;
} // end CoinCounter::DispenseChange()

/*-----------------------------------------------------------------*/
/* implementations of CanDispenser member functions               */
/*-----------------------------------------------------------------*/

CanDispenser::CanDispenser(int dispenserSize_) :    numCans_(dispenserSize_)
// initialize a dispenser
{}

bool CanDispenser::SaleAttempt()
// respond to a button push
// return 0 if no cans left, return 1 if successful sale
{
  if (numCans_ == 0)    // no cans left
  {
    std::cout << "*** SELECTION EMPTY -- please make another selection\n";
    return 0;
  }  // end if
  else                  // success, make sale and decrement numCans_
  {
    --numCans_;
    std::cout << "*** SALE COMPLETE\n";
    return 1;
  }  // end else
} // end CanDispenser::SaleAttempt()

/*-----------------------------------------------------------------*/
/* implementations of SodaMachine member functions                */
/*-----------------------------------------------------------------*/

// Initialize a SodaMachine object and set the price of sodas.  
// Note that this automatically initializes a coin counter and the 
// can dispensers (implicitly, through their constructors).
SodaMachine::SodaMachine(int sodaPrice) : 
  counter_(defaultMachineBankroll),
  cola_(defaultDispenserSize),
  lite_(defaultDispenserSize),
  root_(defaultDispenserSize),
  orng_(defaultDispenserSize),
  free_(defaultDispenserSize),
  price_(sodaPrice)
{}

void SodaMachine::DoCommand(char cmd)
// get a legal character (Q, D, N, R, C, L, B, O, F) and send
// the appropriate message to either the coin counter or a dispenser.
{
  if ((cmd == 'Q') || (cmd == 'D') || (cmd == 'N') || (cmd == 'R'))
    DoCoin(cmd);
  else
    DoSelection(cmd);
  return;
} // end SodaMachine::DoCommand()

void SodaMachine::DoCoin(char cmd)
// respond to a coin insertion or a request to return all coins tendered
{
  int tendered;
  switch(cmd)
  {
    case 'R' : // Return amount tendered
      tendered = counter_.CurrentAmount();
      counter_.TakeAll();
      counter_.DispenseChange(tendered);
      break;
    case 'Q' : counter_.AcceptCoin(25);   break;
    case 'D' : counter_.AcceptCoin(10);   break;
    case 'N' : counter_.AcceptCoin(5);    break;
  } // end switch
  return;
} // end SodaMachine::DoCoin()

void SodaMachine::DoSelection(char cmd)
// Respond to a dispenser button push by determining if there is 
// enough money inserted to make a sale.  If so, send a request
// to make a sale, else do nothing.
{
  bool success;  // 1, if a successful sale, 0 otherwise
  int tendered; // amount inserted so far by customer

  tendered = counter_.CurrentAmount();
  if (tendered < price_)
    std::cout << "*** INSUFFICIENT FUNDS -- Please insert more money\n";
  else
  {
    switch(cmd)               // send sale message to a dispenser
    {
      case 'C' : success = cola_.SaleAttempt();  break;
      case 'L' : success = lite_.SaleAttempt();  break;
      case 'B' : success = root_.SaleAttempt();  break;
      case 'O' : success = orng_.SaleAttempt();  break;
      case 'F' : success = free_.SaleAttempt();  break;
    } // end switch
   
    if (success)      // dispenser signalled a successful sale
    {
      counter_.TakeAll();         // take the money
      if (tendered > price_)       // and make change if needed
        counter_.DispenseChange(tendered - price_);
    } // end if
  } // end else
  return;
}  // end SodaMachine::DoSelection()

/*-----------------------------------------------------------------*/
/* implementations of ServicePerson member functions              */
/*-----------------------------------------------------------------*/

ServicePerson::ServicePerson()
// constructor
// sets std::cout for display of floats as money
{
  std::cout.setf(std::ios::fixed);
  std::cout.setf(std::ios::showpoint);
  std::cout.precision(2);
  return;
} // end ServicePerson::ServicePerson()

void ServicePerson::Inventory(SodaMachine machine)
// displays current amount of money and drinks in machine
{
  std::cout << '\n'
            << "Money on hold:   $"
            << (float(machine.counter_.CurrentAmount()) / 100.0)
            << '\n'
            << "Money in bank:   $"
            << (float(Money(machine.counter_)) / 100.0)
            << '\n'
            << "Drink inventory  C: " << Sodas(machine.cola_) << '\n'
            << "                 L: " << Sodas(machine.lite_) << '\n'
            << "                 B: " << Sodas(machine.root_) << '\n'
            << "                 O: " << Sodas(machine.orng_) << '\n'
            << "                 F: " << Sodas(machine.free_) << "\n\n";
  return;
} // end ServicePerson::inventory()

int ServicePerson::Money(CoinCounter counter)
// return amount of money available (in dollars)
{
  return(counter.inBank_);
} // end ServicePerson::Money()

int ServicePerson::Sodas(CanDispenser dispenser)
// return supply of each drinks
{
  return(dispenser.numCans_);
} // end ServicePerson::Sodas()


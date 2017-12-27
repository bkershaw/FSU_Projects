/*   file: main.cpp

     Driver program -- simulates the life of a soda machine
*/

#include <iostream>      // std::cout
#include <machine.h>     // part of simulation
#include <user.h>        // part of simulation

int main()
{
  SodaMachine     theMachine;        // Initialize a machine
  User            theUser;           // Initialize a user
  ServicePerson   theServicePerson;  // Initialize a service person
   
  char cmd;      // user input
  do             // exit through case 'X'
  {
    cmd = theUser.GetCommand();
    switch(cmd)
    {
      case 'X':
        std::cout << "\nSimulation over -- have a nice day.\n";
        break;
      case 'S': 
        theServicePerson.Inventory(theMachine); 
        break;
      default:
        theMachine.DoCommand(cmd);
    }  // end switch
  }
  while (cmd != 'X');
  // return 0;
}  // end main()


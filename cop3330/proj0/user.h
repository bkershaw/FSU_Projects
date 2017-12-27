/*
   file: user.h 

   Declaration of the class user for the soda machine simulation.
   User object responsibilities are to get a legal command character
   from the keyboard, to respond to two of these (displaying the menu,
   and exiting the simulation) and return the others to the calling
   process.

   NOTE: The soda machine simulation is based on ideas from "The Object
   Concept" by Rick Decker and Stuart Hirshfield, PWS, Boston, 1995.
*/

#ifndef _USER_H
#define _USER_H

class User
{
public:
  User();  // Constructor -- initialize a user object
           // by displaying a banner and showing the menu
  char GetCommand ();         // Return a legal char 

private:
  void ShowMenu   ();         // Show the available choices
  bool IsLegal    (char cmd); // Return true iff cmd is legal
}  ;

#endif


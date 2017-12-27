/*
  fqueue.cpp
  December 3rd 2015
  Blake Kershaw
*/


#include <iostream>
#include <queue.t>

void DisplayMenu();

/*//char
typedef char ElementType;
const size_t maxSize = 10;
const char* eT = "char";
const char ofc = '\0';
*/

//queues of int
typedef int ElementType;
const size_t maxSize = 100;
const char* eT = "int";
const char ofc = ' ';


typedef fsu::Queue<ElementType> QueueType;

template < class Queue >
void CopyTest(Queue s);

template < class Queue >
void AssignTest(const Queue& s);

template < class Queue >
void ConstTest(const Queue& s);


int main()
{
  char selection;
  QueueType queue;
  ElementType Tval;
  std::cout << "This is a Queue < T > test program\n";
  DisplayMenu();
  do
  {
    std::cout << "Enter [command][argument] ('M' for menu, 'Q' to quit): ";
    std::cin >> selection;
    switch (selection)
    {
    case '+':
    case '1':
        std::cin >> Tval;
        queue.Push(Tval);
      break;
    case '-':
    case '2':
      if (!queue.Empty())
        queue.Pop();
      else
        std::cout << "Queue is empty" << std::endl;
      break;
    case 'C':
    case 'c':
      queue.Clear();
      break;
    case 'F':
    case 'f':
      if (!queue.Empty())
        std::cout << "Front of Queue: " << queue.Front() << std::endl;
      else
        std::cout << "Queue is empty" << std::endl;
      break;
    case 'E':
    case 'e':
      if (queue.Empty())
        std::cout << "Queue is empty" << std::endl;
      else
        std::cout << "Queue is not empty" << std::endl;
      break;
    case 'S':
    case 's':
      std::cout << "Queue size     = " << queue.Size() << std::endl;
      break;
    case '=':
      CopyTest(queue);
      AssignTest(queue);
      break;
    case 'D':
    case 'd':
      std::cout << "Queue contents:   ";
      queue.Display(std::cout, ofc);
      std::cout << '\n';
      break;
    case 'U':
    case 'u':
      std::cout << "Queue doesn't have a dump function" << std::endl;
      break;
    case 'M':
    case 'm':
      DisplayMenu();
      break;
    case 'Q':
    case 'q':
      break;
    default:
      std::cout << "  command not found\n";
    }
  } while ((selection != 'Q') && (selection != 'q'));
  std::cout << "\nHave a nice day." << std::endl;
  return 0;
} //end main

void DisplayMenu()
{
  std::cout
    << "Push(Tval)  .............  + or 1\n"
    << "Pop()  ..................  - or 2\n"
    << "Clear()  ................  C\n"
    << "Front()  ................  F\n"
    << "Empty()  ................  E\n"
    << "Size()  .................  S\n"
    << "Copies  .................  =\n"
    << "Display queue ...........  D\n"
    << "Dump() ..................  U\n"
    << "Display this menu  ......  M\n";
}

template < class Queue >
void CopyTest(Queue s)
{
  std::cout << "CopyTest:\n";
  std::cout
    << "Copied object       size: " << s.Size() << '\n'
    << "                contents: ";
  s.Display(std::cout, ofc);
  std::cout << '\n';
}

template < class Queue >
void AssignTest(const Queue& s1)
{
  QueueType s2;
  s2 = s1;
  std::cout << "AssignTest:\n"
    << "Original object     size: " << s1.Size() << '\n'
    << "                contents: ";
  s1.Display(std::cout, ofc);
  std::cout << '\n';
  std::cout
    << "Assignee object     size: " << s2.Size() << '\n'
    << "                contents: ";
  s2.Display(std::cout, ofc);
  std::cout << '\n';
  std::cout << "ConstTest: OK" << std::endl;
}

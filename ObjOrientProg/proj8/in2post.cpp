/*
    in2post.cpp
    11/20/15
    Chris Lacher

    convert infix expression to postfix expression
    this example only works for single letter operands

    Copyright 2012-15, R.C. Lacher
*/

#include <iostream>
#include <queue.t>
#include <stack.t>

const unsigned int colsize = 25;

class Token   // an operator, a parenthesis, or an operand
{
public:
   int IsOperator ();  // am I an operator?
   unsigned char ch;
}  ;  // class Token

//-------------------------------------------
//   operators defined on tokens
//-------------------------------------------

std::ostream& operator << (std::ostream& os, const Token& t)
{
  os << t.ch;
  return os;
}
   
int operator == (Token t1, Token t2)
{
  return t1.ch == t2.ch;
}

int operator != (Token t1, Token t2)
{
  return t1.ch != t2.ch;
}

int operator >= (Token t1, Token t2)
// operator precedance -- NOT a total ordering
{
   int returnval = 0;
   if (t1.ch == t2.ch)
      returnval = 1;

   else
      switch (t1.ch)
      {
         case '*': case '/': case '%':
            switch (t2.ch)
            {
              case '+': case '-':
                 returnval = 1; break;
            }
            break;
      }
   return returnval;
}  // end operator >=()

int operator <= (Token t1, Token t2)
{
  return (t2 >= t1);
}

int operator < (Token t1, Token t2)
{
  return (t2 >= t1 && t1 != t2);
}

int operator > (Token t1, Token t2)
{
  return (t2 > t1);
}

int Token::IsOperator ()
{
   int returnval = 0;
   if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
      returnval = 1;
   return returnval;
}  // end IsOperator()

typedef fsu::Queue < Token > TokenQueue;
typedef fsu::Stack < Token > TokenStack;

void DisplayHeader (std::ostream& os = std::cout)
{
   unsigned int i;
   os << "S";  for (i = 0; i < colsize - 1; ++i) os << ' ';
   os << "Q1"; for (i = 0; i < colsize - 2; ++i) os << ' ';
   os << "Q2\n";
   os << "--"; for (i = 0; i < colsize - 2; ++i) os << ' ';
   os << "--"; for (i = 0; i < colsize - 2; ++i) os << ' '; 
   os << "--\n";
}  // end DisplayHeader()

void Display (TokenStack& S, TokenQueue& Q1, TokenQueue& Q2, std::ostream& os = std::cout)
{
   unsigned int i;
   if (!S.Empty())
   {
      os << S;
      if (colsize > S.Size())
	for (i = 0; i < colsize - S.Size(); ++i)
	  os << ' ';
   }
   else
   {
      os << "NULL";
      if (colsize > 4)
	for (i = 0; i < colsize - 4; ++i)
	  os << ' ';
   }
   if (!Q1.Empty())
   {
      os << Q1;
      if (colsize > Q1.Size())
	for (i = 0; i < colsize - Q1.Size(); ++i)
	  os << ' ';
   }
   else
   {
      os << "NULL";
      if (colsize > 4)
	for (i = 0; i < colsize - 4; ++i)
	  os << ' ';
   }
   if (!Q2.Empty())
   {
      os << Q2;
   }
   else
   {
      os << "NULL";
   }
   os << '\n';
}  // end Display()

int i2p (TokenQueue & Q1, TokenQueue & Q2)
// converts infix expression in Q1 to postfix expression in Q2
{
   Token L, R;
   L.ch = '(';
   R.ch = ')';
   TokenStack S;
   Q2.Clear();
   DisplayHeader();
   Display(S, Q1, Q2);
   while (!Q1.Empty())
   {
      if (Q1.Front() == L)
      // push '(' to mark beginning of a parenthesized expression
      {
         S.Push(Q1.Front());
         Q1.Pop();
         Display(S, Q1, Q2);
      }
      else if (Q1.Front().IsOperator())
      {
         // pop previous operators of equal or higher precedence to output
         while (!S.Empty() && S.Top() >= Q1.Front())
         {
            Q2.Push(S.Top());
            S.Pop();
            Display(S, Q1, Q2);
         }
         // then push new operator onto stack
         S.Push(Q1.Front());
         Q1.Pop();
         Display(S, Q1, Q2);
      }
      else if (Q1.Front() == R)
      // regurgitate operators for the parenthesized expression
      {
         while (!S.Empty() && !(S.Top() == L))
         {
            Q2.Push(S.Top());
            S.Pop();
            Display(S, Q1, Q2);
         }
         if (S.Empty())      // unbalanced parentheses
         {
            std::cout << "** error: too many right parens\n";
            return 0;
         }
         S.Pop();            // discard '('
         Q1.Pop();           // discard ')'
         Display(S, Q1, Q2);
      }
      else                   // t should be an operand
      // send operand directly to output
      {
         Q2.Push(Q1.Front());
         Q1.Pop();
         Display(S, Q1, Q2);
      }
   }  // end while()
   // regurgitate remaining operators
   while (!S.Empty())
   {
      if (S.Top() == L)      // unbalanced parentheses
      {
         std::cout << "** error: too many left parens\n";
         return 0;
      }
      Q2.Push(S.Top());
      S.Pop();
      Display(S, Q1, Q2);
   }
   return 1;
}  // end i2p()

int main(int argc, char* argv[])
{
  bool BATCH = 0;
  if (argc > 1)
  {
    if (argv[1][0] != '\0')
      BATCH = 1;
  }

  std::cout << "\n  Welcome to in2post.\n\n"
	    << "  This program demonstrates the conversion of infix to postfix expressions.\n"
	    << "  No arithmetic is done. For purposes of effective display of the algorithm,\n"
	    << "  only single-character symbols are assumed.\n\n";

   char c;
   TokenQueue Q1, Q2;
   Token t;
   while(1)
   {
     std::cout << "Enter infix expression (0 to quit): ";
     std::cin.get(c);
     if (BATCH) std::cout.put(c);
     if (c == '0')
       {
	 if (BATCH) std::cout.put('\n');
	 break;
       }
     while (c != '\n')
       {
         t.ch = c;
         Q1.Push(t);
         std::cin.get(c);
	 if (BATCH) std::cout.put(c);
       }
     std::cout.put('\n');
     if (i2p(Q1, Q2))
       {
         std::cout << "\n postfix conversion: " << Q2 << '\n';
       }
     else
       {
         std::cout << "\n** syntax error in infix expression" << '\n';
       }
   }  // end while()
   return 0;
}

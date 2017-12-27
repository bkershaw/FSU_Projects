/*
   Find C/C++ Identifiers!!
   Skip over all characters after the line comment
   (treat them as whitespaces).
*/
%{
#include <stdio.h>
#define ID 256
%}
%x COMMENT
%%
\/\/     {BEGIN COMMENT;}
<COMMENT>{
  .   {;}
  \n  { BEGIN INITIAL; }
}
[A-Za-z_][A-Za-z0-9_]*       { return ID; }
.     
\n
%%
int main(void) {
   int toktype;
   while ((toktype = yylex())) {
      switch(toktype) {
        case ID:
            printf("I found the ID: %s\n", yytext);
            break;
        default:
            break;
      }
   }
   return 0;
}

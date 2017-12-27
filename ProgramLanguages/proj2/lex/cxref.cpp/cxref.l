/* The following is an example to find the ident token which only happens outside
   of character context. 
   - Note that the cxref requires to properly handle string and comment contexts */
%{
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>

#define CHAR    256
#define NUM     257
#define IDENT   258
#define INVALID 259

int character = 0;
int string = 0;
int comment = 0;

/* function proto */
void lexical_error(const std::string msg="");
%}

quote    \'
back     \\
ditto    \"
octal    [0-7]
octch    ({back}{octal}|{back}{octal}{octal}|{back}{octal}{octal}{octal})
digit    [0-9]
alpha    [a-zA-Z_]
schar    [^\'\"\n\\]
char     ({back}?({schar}|{ditto})|{back}{back}|{back}{quote}|{octch})

%%
{quote}  { character = !character; }


{alpha}({alpha}|{digit})*       { if (!character) return IDENT; }
{digit}+                        { return NUM;  }
<<EOF>>                         { return EOF;  }
.                               { ; }
%%
/*******************/
/* c/c++ functions */
/*******************/

int main() {
    int tok;
    while ((tok = yylex()) != EOF) {
      switch(tok) {
      case IDENT: std::cout << "Found ID token = " << yytext << std::endl;
               break;
      case NUM: std::cout << "Found NUM token = " << yytext << std::endl;
               break;
      case CHAR: std::cout << "Found CHAR token = " << yytext << std::endl;
               break;
      default:
              lexical_error("I don't know what this token is");
              exit(1);
      }
    }
    return 0;
}

int yywrap() {
   std::cout << "Bye Bye!\n";
   return 1;
}

void lexical_error(const std::string msg) {
  std::cout << msg << std::endl;
} 

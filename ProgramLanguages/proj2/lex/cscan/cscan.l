/* The following is an example to find the char token, num token,
   and ident token, which is a subset of the original C scan project
   - Note that the exercise doesn't handle comment */
%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define CHAR    256
#define NUM     257
#define IDENT   258
#define INVALID 259

/* function proto */
void lexical_error(char *);
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


%x CHARACTER
%%
{quote}  { yymore(); BEGIN CHARACTER; }

<CHARACTER>{
    {quote}  { yymore(); BEGIN INITIAL; return CHAR;}
    {char}   { yymore();}
    .
}

{alpha}({alpha}|{digit})*       { return IDENT; }
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
      case IDENT: printf("Found ID token = %s\n", yytext);
               break;
      case NUM: printf("Found NUM token = %d\n", atoi(yytext));
               break;
      case CHAR: printf("Found CHAR token = %s\n", yytext);
               break;
      default:
              lexical_error("I don't know what this token is");
              exit(1);
      }
    }
    return 0;
}

int yywrap() {
   printf("Bye Bye!\n");
   return 1;
}

void lexical_error(char *msg) {
  printf("%s\n", msg);
} 

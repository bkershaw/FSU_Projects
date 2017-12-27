/* CODE */

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define CHAR    256
#define NUM     257
#define IDENT   258
#define INVALID 259

int character = 0;
int string = 0;
int comment = 0;

/* function proto */
void lexical_error(char *);
%}

quote      \'
forward    /
asterick   *
back       \\
ditto      \"
comm    ( {forward}{forward} | {forward}{asterick} )
endComm ( {asterick}{forward} )
octal      [0-7]
octch      ({back}{octal}|{back}{octal}{octal}|{back}{octal}{octal}{octal})
digit      [0-9]
alpha      [a-zA-Z_]
schar      [^\'\"\n\\]
char       ({back}?({schar}|{ditto})|{back}{back}|{back}{quote}|{octch})

%x CHARACTER
%x STRING
%x COMMENT

%%
{comm} { BEGIN COMMENT; }

<COMMENT>{
    {comm}    { BEGIN INITIAL; }
    {endComm} 
    .          
}

{ditto}  { BEGIN CHARACTER; }

<STRING>{
    {ditto}   { BEGIN INITIAL; }
    .         { ; }
}


{quote}  { BEGIN CHARACTER; }

<CHARACTER>{
    {quote}   { BEGIN INITIAL; }
    {char}    { ; }
    .         { ; }
}


"auto"                   { ; }
"break"                  { ; }
"case"                   { ; }
"const"                  { ; }
"continue"               { ; }
"default"                { ; }
"do"                     { ; }
"double"                 { ; }
"else"                   { ; }
"extern"                 { ; }
"float"                  { ; }
"for"                    { ; }
"goto"                   { ; }
"if"                     { ; }
"int"                    { ; }
"long"                   { ; }
"register"               { ; }
"return"                 { ; }
"short"                  { ; }
"signed"                 { ; }
"sizeof"                 { ; }
"static"                 { ; }
"struct"                 { ; }
"switch"                 { ; }
"typedef"                { ; }
"union"                  { ; }
"unsigned"               { ; }
"void"                   { ; }
"while"                  { ; }
"enum"                   { ; }
"volatile"               { ; }


{alpha}({alpha}|{digit})*       { if (!CHARACTER) return IDENT; }
{digit}+                        { ; }
<<EOF>>                         { ; }
.                               { ; }
%%

int main() {
     int tok;
     while ((tok == yylex()) != EOF{
          switch(tok) {
            case CHAR: 
               printf( "%s:/n", yytext );
               break;
            default:
               printf("no match for %s", yytext );
               break;
          }
     }
     return 0;
}

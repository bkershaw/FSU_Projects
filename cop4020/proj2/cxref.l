/**************************************************************
 *                                                            *
 *               Name: Blake Kershaw                          *
 *                Class: COP 4020                             *
 *       Assignment: Project 2(lexical analysis for a         *
 *                             C cross reference listing)     *  
 *                Compile: with attached makefile             *
 *                                                            *
 *************************************************************/

%{
#include <cstdio>
#include <string>
#include <list>
#include <map>
#include <cctype>
#include <iostream>
#include <iomanip>

#define CHAR    256
#define NUM     257
#define IDENT   258
#define INVALID 259

int character = 0;
int s = 0;
int comment = 0;
int lineCount = 1;
int control = 0;
int pre = 0;

std::map<std::string,std::list<int> > m ;

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

%x PROCESSOR
%x COMM

%%

"auto"                   { ; }
"break"                  { ; }
"case"                   { ; }
"char"                   { ; }
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

\\\\                            { ; }
\\\"                            { ; }
\\\'                            { ; } 
\\                              { ; }
{ditto}                         { if (!character) s = ~s; }
{quote}                         { if(!s) character = ~character; }

\/\/                            { if (!character && !s) BEGIN COMM; }
<COMM>{
   .   { ; }
   \n  { ++lineCount; BEGIN INITIAL; } 
}
  
#{alpha}({alpha}|{digit})*     { if (!character && !s && !comment) BEGIN PROCESSOR; }
<PROCESSOR>{
   .   { ; }      
   \n  { ++lineCount; BEGIN INITIAL;}
}

"/*"                            { comment = ~comment; }
"*/"                            { comment = 0; }
\n                              { ++lineCount; }
{alpha}({alpha}|{digit})*       { if( !character && !s && !comment  ) return IDENT; }
{digit}+                        { ; }
.                               { ; }
<<EOF>>                         { return EOF; }
%%

int main() {
     int tok;

    /*Loop to scan redirected file */
     while ( ( tok = yylex() ) != EOF ){
          switch(tok) {
            case IDENT: 
               //printf( "%s\n", yytext );
               if(m[yytext].back() != lineCount)
                  m[yytext].push_back(lineCount);              
               break;
            default:
               printf("no match for: %s\n", yytext );
               exit(1);
          } //end switch
     } //end while

        /* DUMP LEXICAL ANALYSIS IN ALPHABETICAL ORDER WITH CORRESPONDING LINE NUMBERS */ 
      for(std::map<std::string, std::list<int> >::const_iterator it = m.begin(); it != m.end(); ++it){
          std::cout << std::setw(25) << it->first << ": "; //prints identifer
          for(std::list<int>::const_iterator lit = it->second.begin(); lit != it->second.end(); lit++){
            if( m[it->first].front() == *lit )      
               std::cout << *lit; //no comma on first element of list
            else
	       std::cout << ", " <<  *lit;
	  } 
          std::cout << std::endl; 
      } 
      return 0;
} //end main




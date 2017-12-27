/* for each occurrence of string "hell" print "Hello COP4020" */
%{
 #include <cstdio>
 #include <iostream>
 #include <cstdlib>
 #include <cctype>
 #include <map>

#define ID 256
 int lineno = 1;
%}
%%
"**"     { std::cout << "double *\n"; }
\n       { lineno++; }
"\\n"    { std::cout << "new line as a string\n"; }
hell     { std::cout << "Hello COP4020 : lineno" <<  lineno << std::endl;
           return ID;
         }
<<EOF>>  { return EOF; }
.        { ; }
%%
int main(void) {
  lineno = 0;
  int type;
  while ((type = yylex()) != EOF) {
     switch (type) {
       case ID:
           // do something
           std::cout << "I found the pattern\n";
           break;
       default:
           break;
     }
  }
  return 0;
}



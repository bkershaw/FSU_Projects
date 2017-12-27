/* for each occurrence of string "hell" print "Hello COP4020" */
%{
 #include <stdio.h>
 #define ID 256
 int lineno;
%}
%%
\n       { lineno++; }
hell     { printf("Hello COP4020 : lineno %d \n", lineno);
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
           printf("I found the pattern\n");
           break;
       default:
           break;
     }
  }
  return 0;
}



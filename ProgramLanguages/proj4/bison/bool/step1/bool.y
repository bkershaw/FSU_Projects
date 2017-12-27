%{
#include <stdio.h>

void yyerror(char *);
%}
    
%token OR AND NOT 
%token TRUE FALSE

%%
prog: exprs
    ;
exprs: 
    | exprs expr ';'  
    ;
expr: expr OR term     
   | term            
   ;
term : term AND fact 
   | fact            
   ;
fact : NOT fact      
     | TRUE          
     | FALSE         
     ;
%%
int main() {
   if (yyparse())
      printf("syntactically incorrect\n");
   else
     printf("syntactically correct\n");
   return 0;
}

void yyerror(char *s) {
  fprintf(stderr, "Syntax error : %s\n", s);
}



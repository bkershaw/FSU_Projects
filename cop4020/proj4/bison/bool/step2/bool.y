%{
#include <stdio.h>
void yyerror(char *);
%}

%union {
  unsigned char val;
}

%token AND OR NOT
%token<val> TRUE FALSE
%type<val> factor term expr
%%
prog: exprs
    ;
exprs:
     | exprs expr ';' { if ($2) printf("oh yes, true!\n"); 
                        else    printf("oh no, false!\n"); }
     ;
expr : expr OR term { $$ = $1 | $3; }
     | term { $$ = $1; }
     ;
term : term AND factor { $$ = $1 & $3; }
     | factor { $$ = $1; }
     ;
factor: NOT factor { $$ = ~$2 ; }
     | TRUE   { $$ = $1; }
     | FALSE  { $$ = $1; }
     ;
%%
int main() {
   if (yyparse() == 0)   // yylex() 
      printf("syntax is ok\n");
   else
      printf("syntax is incorrect\n");
   return 0;
}

void yyerror(char *s) {
      fprintf(stderr, "something wrong %s\n", s);
}

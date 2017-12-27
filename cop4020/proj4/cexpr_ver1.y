%{
  #include <stdio.h>

  void yyerror(char *);
  int yylex(void);

  int sym[26];

  int computeSymbolIndex(char token);
  int symVal(char symbol);
  void updateSymbolVal(char symbol, int num);
  void dump();
  %}

   %union{ int val; char var; }

%token dump
%token <var> VARIABLE
%token <val> INTEGER
%left '+' '-'
%left '*' '/'
%type  <val> assignment
%type  <val> program expr term

%%

program:    program assignment ';'  { printf("%d\n", $2);}
          | program expr ';'        { printf("%d\n", $2); }
          | dump ';'                { dump(); }
          |  
          ;

assignment: VARIABLE '=' expr      {updateSymbolVal($1,$3);}
          ;
 
expr:      term                     { $$ = $1;}
          | expr '+' term           { $$ = $1 + $3; }
          | expr '-' term           { $$ = $1 - $3; }
          | expr '*' term           { $$ = $1 * $3; }
          | expr '/' term           { $$ = $1 / $3; }
          | '(' expr ')'            { $$ = $2; }
          ;

term      : INTEGER                 { $$ = $1; } 
          | VARIABLE                { $$ = symbolVal($1); }
          ;

%%

int main(void) {
  /* init symbol table */
  int i;
  for(i=0; i<26; i++) {
  sym[i] = 0;
 }
  
  return yyparse();
}

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

 int computeSymbolIndex(char token)
 {
  int idx = -1;
  idx = token - 'a';
  return idx;
 } 

 /* returns the value of a given symbol */
 int symbolVal(char symbol)
 {
  int bucket = computeSymbolIndex(symbol);
  return sym[bucket];
 }

 /* updates the value of a given symbol */
 void updateSymbolVal(char symbol, int num)
 {
  int bucket = computeSymbolIndex(symbol);
  sym[bucket] = num;
 }

/*dump*/
void dump(){
  char letter = 'a';
  for(int i = 0; i < 26; ++i;){
    letter + i; 
    printf("%c:  &d\n", letter, sym[i]);
  }
}

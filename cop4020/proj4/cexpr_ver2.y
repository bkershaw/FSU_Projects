%{
  #include <stdio.h>

  void yyerror(char *);
  int yylex(void);

  struct v{
     int num;
     bool valid;
  }; 

  struct v sym[26];

  int computeSymbolIndex(char token);
  int symVal(char symbol);
  void updateSymbolVal(char symbol, int num);
  void dup();
  %}

   %union{ int val; char var; }

%token dump
%token <var> VARIABLE
%token <val> INTEGER
%left '+' '-'
%left '*' '/'
%type <val> program expr term assignment

%%

program  : expr ';'        { printf("%d\n", $2); }
         | assignment ';'  { printf("%d\n", $1); }
         | dump ';'        { dup(); }    
         ;

assignment: VARIABLE '=' expr      {updateSymbolVal($1,$3); $$ = $3;}
 
expr      : term                   { $$ = $1; }
         | expr '+' term           { $$ = $1 + $3; }
         | expr '-' term           { $$ = $1 - $3; }
         | expr '*' term           { $$ = $1 * $3; }
         | expr '/' term           { $$ = $1 / $3; }
         | '(' expr ')'            { $$ = $2; }
         ;

term     : INTEGER                { $$ = $1; } 
         | VARIABLE               { $$ = symbolVal($1); }
         ;

%%

int main(void) {
  /* init symbol table */
  int i;
  for(i=0; i<26; i++) {
  sym[i].num = 0;
  sym[i].valid = false;
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
  return sym[bucket].num;
 }

 /* updates the value of a given symbol */
 void updateSymbolVal(char symbol, int n)
 {
  int bucket = computeSymbolIndex(symbol);
  sym[bucket].num = n;
 }

/*dump*/
void dup(){
  char letter = 'a';
 for(int i = 0; i < 26; i++){
    char newL =    letter + i;
    if( sym[i].valid)
      printf("%c:  %d\n", newL, sym[i].num);
    else
      printf("%c:  unkown\n", newL);
  }
}

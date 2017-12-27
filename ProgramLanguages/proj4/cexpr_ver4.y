/**************************************************************
 *                                                            *
 *               Name: Blake Kershaw                          *
 *                Class: COP 4020                             *
 *       Assignment: Project 4                                *
 *                Compile: with attached makefile             *
 *      g++ -std=c++11 lex.yy.c y.tab.c -o c.exe -lfl         *
 *************************************************************/


%{
  #include <stdio.h>

  void yyerror(char*);
  int yylex(void);

  struct v{
     int num;
     bool valid;
  }; 

  struct v sym[26];
  bool control = false;

  int computeSymbolIndex(char token);
  int symbolVal(char symbol);
  void updateSymbolVal(char symbol, int num);
  void dup();
  void res();
  void init();
  %}

   %union{ int val; char var; }

%token dump
%token reset
%token <var> VARIABLE
%token <val> INTEGER
%left '+' '-'
%left '*' '/'
%type <val> expr term assignment

%%

program  : exprs
         ;

exprs    :   
         | exprs expr ';'        { printf("%d\n", $2); }
         | exprs assignment ';'  { if(control) control = false;
                                   else        printf("%d\n", $2); }
         | exprs dump ';'        { dup(); }    
         | exprs reset ';'       { res(); }                 
         ;

assignment: VARIABLE '=' expr { if(control) control = false;
                                else        updateSymbolVal($1,$3); $$ = $3;}
          ;
 
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

int main() {
  init();
  yyparse();
  return 0;
}

void yyerror(char *s) {
  fprintf(stderr, "somethings wrong%s\n", s);
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
 

  if( sym[bucket].valid == false )     {
    printf("unknown");
    control = true;
  }

  return sym[bucket].num;
  
 }

 /* updates the value of a given symbol */
 void updateSymbolVal(char symbol, int n)
 {
  int bucket = computeSymbolIndex(symbol);
  sym[bucket].num = n;
  sym[bucket].valid = true;
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

/*reset variables to unknown*/
void res(){
  int i;
  for(i=0; i<26; i++) {
     sym[i].num = 0;
     sym[i].valid = false;
  }
}

/* init symbol table */
void init(){   
  int i;
  for(i=0; i<26; i++) {
  sym[i].num = 0;
  sym[i].valid = false;
 }
}

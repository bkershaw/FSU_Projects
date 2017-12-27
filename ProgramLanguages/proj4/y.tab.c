#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 11 "cexpr.y"
  #include <stdio.h>
  #include <string>
  #include <cstring>
  #include <iostream>

  void yyerror(const char*);
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
  
#line 35 "cexpr.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ int val; char var; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 52 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define reset 257
#define dump 258
#define increment 259
#define decrement 260
#define s_l 261
#define s_r 262
#define VARIABLE 263
#define INTEGER 264
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,   14,   14,   14,   14,    2,    2,   12,   12,   11,
   11,   10,   10,    9,    9,    9,    8,    8,    8,    3,
    3,    3,    3,    7,    7,    6,    6,    5,    5,    5,
    4,    4,    4,   13,   13,    1,    1,
};
static const short yylen[] = {                            2,
    1,    0,    2,    2,    3,    1,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    3,    1,    3,    3,    1,
    3,    3,    3,    1,    2,    1,    2,    1,    2,    2,
    1,    2,    2,    1,    3,    1,    1,
};
static const short yydefred[] = {                         2,
    0,    0,    4,    3,    0,    0,    0,   36,    0,    0,
    0,   34,    0,    0,   28,   26,   24,   20,    0,    0,
    0,    0,    0,   31,   29,   30,   32,   33,    0,    0,
   25,   27,    0,    5,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    7,   35,   21,   22,   23,    0,
    0,    0,    0,    0,    0,    0,
};
static const short yydgoto[] = {                          1,
   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
   22,   23,   24,    2,
};
static const short yysindex[] = {                         0,
    0,  -31,    0,    0, -260, -256,  -59,    0,  -10,   -2,
   -8,    0,  -48,   39,    0,    0,    0,    0,  -17, -199,
  -18,  -38,  -66,    0,    0,    0,    0,    0,   -8, -177,
    0,    0,   23,    0,  -10,  -10,  -10,  -10,  -10,  -10,
  -10,  -10,  -10,  -10,    0,    0,    0,    0,    0,   39,
   39,  -17,  -17, -199,  -18,  -38,
};
static const short yyrindex[] = {                         0,
    0,   72,    0,    0,    0,    0,  -37,    0,    0,    0,
    0,    0,    0,  -26,    0,    0,    0,    0,    2,  -25,
   -5,    1,   14,    0,    0,    0,    0,    0,    0,  -37,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -20,
  -14,    6,    8,   12,    7,   11,
};
static const short yygindex[] = {                         0,
    0,   30,   46,    0,    0,   65,   42,   50,   51,   45,
   48,    0,    0,    0,
};
#define YYTABLESIZE 270
static const short yytable[] = {                         37,
   37,   29,   25,   37,   37,   37,   26,   37,   11,   37,
   34,   17,   12,    9,   17,   12,   17,   18,   17,   42,
   18,   37,   18,   19,   18,   38,   19,   39,   19,   11,
   19,   11,   17,   12,    9,   10,    9,   11,   18,   14,
   33,    8,   14,   15,   19,   16,   15,   11,   16,   13,
   31,    9,   13,   10,    6,   43,   37,   44,   45,    8,
   14,   40,   41,   46,   15,   11,   16,   17,   12,    9,
   13,    1,    6,   18,   32,   37,   47,   48,   49,   19,
   35,   27,   28,   50,   51,   36,   37,   55,   10,   52,
   53,   56,   54,    0,   10,   14,    0,   17,   12,   15,
   11,   16,    0,   18,    0,   13,    0,    0,    0,   19,
    0,    0,    0,    0,    0,   10,    0,   10,   10,    0,
    0,    0,    0,   10,    8,   14,    0,    0,    0,   15,
   11,   16,    0,    0,    9,   13,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   27,
   28,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   37,   37,    3,    4,    5,    6,    0,
    0,    7,    8,    0,   17,   17,    0,    0,    0,    0,
   18,   18,    0,    0,    0,    0,   19,   19,    5,    6,
    5,    6,   30,    8,    7,    8,    5,    6,    0,    0,
   30,    8,   14,   14,    0,    0,   15,   15,   16,   16,
};
static const short yycheck[] = {                         37,
   38,   61,  263,   41,   42,   43,  263,   45,   40,   47,
   59,   38,   38,   45,   41,   41,   43,   38,   45,   38,
   41,   59,   43,   38,   45,   43,   41,   45,   43,   40,
   45,   40,   59,   59,   45,   41,   45,   40,   59,   38,
   11,   41,   41,   38,   59,   38,   41,   41,   41,   38,
    9,   41,   41,   59,   41,   94,   94,  124,   29,   59,
   59,  261,  262,   41,   59,   59,   59,   94,   94,   59,
   59,    0,   59,   94,   10,   37,   35,   36,   37,   94,
   42,  259,  260,   38,   39,   47,  124,   43,   94,   40,
   41,   44,   42,   -1,  126,   94,   -1,  124,  124,   94,
   94,   94,   -1,  124,   -1,   94,   -1,   -1,   -1,  124,
   -1,   -1,   -1,   -1,   -1,  126,   -1,  126,  124,   -1,
   -1,   -1,   -1,  126,  124,  124,   -1,   -1,   -1,  124,
  124,  124,   -1,   -1,  124,  124,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,
  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  261,  262,  257,  258,  259,  260,   -1,
   -1,  263,  264,   -1,  261,  262,   -1,   -1,   -1,   -1,
  261,  262,   -1,   -1,   -1,   -1,  261,  262,  259,  260,
  259,  260,  263,  264,  263,  264,  259,  260,   -1,   -1,
  263,  264,  261,  262,   -1,   -1,  261,  262,  261,  262,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 264
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,
0,"';'",0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,"'~'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"reset","dump","increment","decrement","s_l","s_r","VARIABLE",
"INTEGER",
};
static const char *yyrule[] = {
"$accept : program",
"program : exprs",
"exprs :",
"exprs : exprs dump",
"exprs : exprs reset",
"exprs : exprs assignment ';'",
"assignment : or",
"assignment : VARIABLE '=' assignment",
"or : xor",
"or : or '|' xor",
"xor : and",
"xor : xor '^' and",
"and : shift",
"and : and '&' shift",
"shift : add_sub",
"shift : shift s_l add_sub",
"shift : shift s_r add_sub",
"add_sub : md",
"add_sub : add_sub '+' md",
"add_sub : add_sub '-' md",
"md : negation",
"md : md '*' negation",
"md : md '/' negation",
"md : md '%' negation",
"negation : not",
"negation : '-' negation",
"not : pre",
"not : '~' not",
"pre : post",
"pre : increment VARIABLE",
"pre : decrement VARIABLE",
"post : paren",
"post : VARIABLE increment",
"post : VARIABLE decrement",
"paren : term",
"paren : '(' assignment ')'",
"term : INTEGER",
"term : VARIABLE",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 112 "cexpr.y"

int main() {
  init();
  yyparse();

  std::cout << "\nCalculator off." << std::endl;

  return 0;
}

void yyerror(const char *s) {
  printf("somethings wrong: %s\n", s);
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
 

  if( sym[bucket].valid == false )     
    control = true;  

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
      printf("%c: %d\n", newL, sym[i].num);
    else
      printf("%c: unknown\n", newL);
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
#line 363 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 48 "cexpr.y"
	{ dup(); }
break;
case 4:
#line 49 "cexpr.y"
	{ res(); }
break;
case 5:
#line 50 "cexpr.y"
	{ if(!control) printf("%d\n", yystack.l_mark[-1].val); else printf("unknown\n");
                                                                          control = false; }
break;
case 6:
#line 54 "cexpr.y"
	{yyval.val = yystack.l_mark[0].val;}
break;
case 7:
#line 55 "cexpr.y"
	{ if(!control) updateSymbolVal(yystack.l_mark[-2].var,yystack.l_mark[0].val); yyval.val = yystack.l_mark[0].val;}
break;
case 8:
#line 58 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val; }
break;
case 9:
#line 59 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val | yystack.l_mark[0].val; }
break;
case 10:
#line 62 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val; }
break;
case 11:
#line 63 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val ^ yystack.l_mark[0].val; }
break;
case 12:
#line 66 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;}
break;
case 13:
#line 67 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val & yystack.l_mark[0].val; }
break;
case 14:
#line 70 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;}
break;
case 15:
#line 71 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val << yystack.l_mark[0].val;}
break;
case 16:
#line 72 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val >> yystack.l_mark[0].val;}
break;
case 17:
#line 75 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val; }
break;
case 18:
#line 76 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val + yystack.l_mark[0].val; }
break;
case 19:
#line 77 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val - yystack.l_mark[0].val; }
break;
case 20:
#line 80 "cexpr.y"
	{ yyval.val= yystack.l_mark[0].val; }
break;
case 21:
#line 81 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val * yystack.l_mark[0].val; }
break;
case 22:
#line 82 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val / yystack.l_mark[0].val; }
break;
case 23:
#line 83 "cexpr.y"
	{ yyval.val = yystack.l_mark[-2].val % yystack.l_mark[0].val; }
break;
case 24:
#line 86 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;     }
break;
case 25:
#line 87 "cexpr.y"
	{ yyval.val = -yystack.l_mark[0].val;    }
break;
case 26:
#line 90 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;     }
break;
case 27:
#line 91 "cexpr.y"
	{ yyval.val = ~yystack.l_mark[0].val;    }
break;
case 28:
#line 94 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;                        }
break;
case 29:
#line 95 "cexpr.y"
	{ yystack.l_mark[0].var = symbolVal(yystack.l_mark[0].var); yyval.val = ++yystack.l_mark[0].var;  }
break;
case 30:
#line 96 "cexpr.y"
	{ yystack.l_mark[0].var = symbolVal(yystack.l_mark[0].var); yyval.val = --yystack.l_mark[0].var;  }
break;
case 31:
#line 99 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;                        }
break;
case 32:
#line 100 "cexpr.y"
	{ yystack.l_mark[-1].var = symbolVal(yystack.l_mark[-1].var); yyval.val = yystack.l_mark[-1].var++;  }
break;
case 33:
#line 101 "cexpr.y"
	{ yystack.l_mark[-1].var = symbolVal(yystack.l_mark[-1].var); yyval.val = yystack.l_mark[-1].var--;  }
break;
case 34:
#line 104 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;     }
break;
case 35:
#line 105 "cexpr.y"
	{ yyval.val = yystack.l_mark[-1].val;     }
break;
case 36:
#line 108 "cexpr.y"
	{ yyval.val = yystack.l_mark[0].val;            }
break;
case 37:
#line 109 "cexpr.y"
	{ yyval.val = symbolVal(yystack.l_mark[0].var); }
break;
#line 710 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}

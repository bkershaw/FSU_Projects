#define reset 257
#define dump 258
#define increment 259
#define decrement 260
#define s_l 261
#define s_r 262
#define VARIABLE 263
#define INTEGER 264
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ int val; char var; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

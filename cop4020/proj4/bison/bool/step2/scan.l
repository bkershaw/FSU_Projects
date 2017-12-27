%{
#include "bool.h"
%}
%%
and   { return AND; }
or    { return OR; }
not   { return NOT; }
true  { yylval.val = 1; return TRUE; }
false { yylval.val = 0; return FALSE; }
[ \t]+ ;
\n     ;
.     { return *yytext; }
%%

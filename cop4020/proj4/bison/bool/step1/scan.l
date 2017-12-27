%{
#include "bool.h"
%}



%%
(true|TRUE)     { return TRUE; }
(false|FALSE)   { return FALSE;}
[ \t]+          ;
\n              ;
(and|AND)       { return AND;}
(or|OR)         { return OR;}
(not|NOT)       { return NOT;}
.               { return *yytext; }

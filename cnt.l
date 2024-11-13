%{
#include "cnt.tab.h"
%}

%%

[a-zA-Z]+   { yylval.str = strdup(yytext); return WORD; }
[ \t\n]+    ;  // Ignore whitespace
.           ;  // Ignore any other characters

%%

int yywrap() {
    return 1;
}

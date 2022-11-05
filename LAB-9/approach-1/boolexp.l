/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
# include "boolexp.h"
# include "boolexp.tab.h"
%}
%%
"." |
"+" { return yytext[0];}
[a-zA-Z]+ { yylval.c = yytext[0]; return CHAR; }
\n { return EOL; }
"//".*
[ \t] { /* ignore whitespace */ }
. { yyerror("Unidentified character %c\n", *yytext); }
%%
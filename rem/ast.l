/* recognize tokens for the calculator */
%option noyywrap nodefault yylineno
%{
# include "ast.h"
# include "ast.tab.h"
%}
/* float exponent */
EXP ([Ee][-+]?[0-9]+)
%%
"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")" { return yytext[0];}
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }
\n { return EOL; }
"//".*
[ \t] { /* ignore whitespace */ }
. { yyerror("Mystery character %c\n", *yytext); }
%%
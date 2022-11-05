/* recognize tokens for the calculator */
%option noyywrap
%{
# include "parser.tab.h"

void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
%}
%%
"." { return AND; }
"+" { return OR; }
[a-zA-Z]+ { yylval = yytext[0]; return CHAR; }
\n { return EOL; }
"//".*
[ \t] { /* ignore whitespace */ }
. { yyerror("Unidentified character %c\n"); }
%%
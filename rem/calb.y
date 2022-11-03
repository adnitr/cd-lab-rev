%{
#include <stdio.h>
int yylex();
int yyerror();
%}
/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%%
calclist: /* nothing */
| calclist exp EOL { printf("= %d\n", $2); }
;
exp: factor
| exp ADD factor { $$ = $1 + $3; }
| exp SUB factor { $$ = $1 - $3; }
;
factor: term1
| factor MUL term1 { $$ = $1 * $3; }
;
term1: term2
| term1 DIV term2 { $$ = $1 / $3; }
;
term2: NUMBER
| ABS term2 { $$ = $2 >= 0? $2 : - $2; }
;
%%
int main(int argc, char **argv)
{
yyparse();
}
int yyerror(char *s)
{
fprintf(stderr, "error: %s\n", s);
}
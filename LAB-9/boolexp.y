/* calculator with AST */
%{
# include <stdio.h>
# include <stdlib.h>
# include "boolexp.h"
%}

%union {
    struct ast *a;
    char c;
}

%token <c> CHAR
%token EOL

%type <a> exp factor term
%left '+'
%left '.'

%%
calclist: /* nothing */
| calclist exp EOL {
    printf("= %s\n", eval($2));
    treefree($2);
    printf("> ");
}
| calclist EOL { printf("> "); } /* blank line or a comment */
;

exp: factor
| exp '+' factor { $$ = newast('+', $1,$3);}
;

factor: term
| factor '.' term {$$ = newast('.', $1,$3);}
;

term: CHAR { $$ = newchar($1); }
| '(' exp ')' { $$ = $2; }
;
%%
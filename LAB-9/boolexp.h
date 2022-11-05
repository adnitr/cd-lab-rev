/*
* Declarations for a boolexp evaluator
*/

/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);

/* nodes in the abstract syntax tree */
struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct charval {        //type K for constant
    int nodetype;
    char c;
};

/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newchar(char c);

/* evaluate an AST */
char* eval(struct ast *);

/* delete and free an AST */
void treefree(struct ast *);
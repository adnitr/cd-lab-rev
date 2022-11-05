#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "boolexp.h"

char NAN[50][50]; // NAND and NOT
char NON[50][50]; // NAND and NOT
int rowNAN = 0, rowNON = 0;

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newchar(char c)
{
    struct charval *a = malloc(sizeof(struct charval));
    if (!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->c = c;
    return (struct ast *)a;
}

char *insertNAN(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        NAN[rowNAN][i] = s[i];
    }
    int temp = rowNAN++;
    return NAN[temp];
}

char *insertNON(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        NON[rowNON][i] = s[i];
    }
    int temp = rowNON++;
    return NON[temp];
}

char *evalOR_NAN(char *a, char *b)
{
    char resStr[50];
    int ptr = 0;

    // a+b => (a'.b')'

    resStr[ptr++] = '(';

    int i = 0;
    while (a[i] != '\0')
    {
        resStr[ptr++] = a[i];
        i++;
    }

    ptr--;
    if (resStr[ptr] != '\'')
    {
        ptr++;
        resStr[ptr++] = '\'';
    }

    resStr[ptr++] = '.';

    i = 0;
    while (b[i] != '\0')
    {
        resStr[ptr++] = b[i];
        i++;
    }

    ptr--;
    if (resStr[ptr] != '\'')
    {
        ptr++;
        resStr[ptr++] = '\'';
    }
    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr] = '\0';

    return insertNAN(resStr);
}

char *evalOR_NON(char *a, char *b)
{
    char resStr[50];
    int ptr = 0;

    // a+b => ((a+b)')'

    resStr[ptr++] = '(';
    resStr[ptr++] = '(';

    int i = 0;
    while (a[i] != '\0')
    {
        resStr[ptr++] = a[i];
        i++;
    }

    resStr[ptr++] = '+';

    i = 0;
    while (b[i] != '\0')
    {
        resStr[ptr++] = b[i];
        i++;
    }

    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr] = '\0';

    return insertNON(resStr);
}

char *evalAND_NAN(char *a, char *b)
{
    char resStr[50];
    int ptr = 0;

    // a.b => ((a.b)')'

    resStr[ptr++] = '(';
    resStr[ptr++] = '(';

    int i = 0;
    while (a[i] != '\0')
    {
        resStr[ptr++] = a[i];
        i++;
    }

    resStr[ptr++] = '.';

    i = 0;
    while (b[i] != '\0')
    {
        resStr[ptr++] = b[i];
        i++;
    }

    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr] = '\0';

    return insertNAN(resStr);
}

char *evalAND_NON(char *a, char *b)
{
    char resStr[50];
    int ptr = 0;

    // a.b => (a'+b')'

    resStr[ptr++] = '(';

    int i = 0;
    while (a[i] != '\0')
    {
        resStr[ptr++] = a[i];
        i++;
    }

    ptr--;
    if (resStr[ptr] != '\'')
    {
        ptr++;
        resStr[ptr++] = '\'';
    }

    resStr[ptr++] = '+';

    i = 0;
    while (b[i] != '\0')
    {
        resStr[ptr++] = b[i];
        i++;
    }

    ptr--;
    if (resStr[ptr] != '\'')
    {
        ptr++;
        resStr[ptr++] = '\'';
    }

    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr] = '\0';

    return insertNON(resStr);
}

char *evalK_NAN(char c)
{
    char resStr[2];
    resStr[0] = c;
    resStr[1] = '\0';
    return insertNAN(resStr);
}

char *evalK_NON(char c)
{
    char resStr[2];
    resStr[0] = c;
    resStr[1] = '\0';
    return insertNON(resStr);
}

struct strset eval(struct ast *a)
{
    char *strNAN;
    char *strNON;
    // calculated value of this subtree
    switch (a->nodetype)
    {
    case 'K':
        strNAN = evalK_NAN(((struct charval *)a)->c);
        strNON = evalK_NAN(((struct charval *)a)->c);
        break;
    case '+':
        strNAN = evalOR_NAN((eval(a->l)).strNAN, (eval(a->r)).strNAN);
        strNON = evalOR_NON((eval(a->l)).strNON, (eval(a->r)).strNON);
        break;
    case '.':
        strNAN = evalAND_NAN((eval(a->l)).strNAN, (eval(a->r)).strNAN);
        strNON = evalAND_NON((eval(a->l)).strNON, (eval(a->r)).strNON);
        break;
    default:
        printf("internal error: bad node %c\n", a->nodetype);
    }

    struct strset s;
    s.strNAN = strNAN;
    s.strNON = strNON;

    return s;
}

void treefree(struct ast *a)
{
    switch (a->nodetype)
    {
    /* two subtrees */
    case '+':
    case '.':
        treefree(a->r);
    /* no subtree */
    case 'K':
        free(a);
        break;
    default:
        printf("internal error: free bad node %c\n", a->nodetype);
    }
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main()
{
    printf("> ");
    return yyparse();
}
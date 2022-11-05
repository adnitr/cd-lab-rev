#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "boolexp.h"

char ans[100][100];
int row = 0;

char *insert(char carr[][100], char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        carr[row][i] = s[i];
    }
    int temp = row++;
    return carr[temp];
}

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

char *evaluateOR(char *a, char *b)
{
    char resStr[100];
    resStr[0] = '(';
    resStr[1] = '(';
    int i = 0;
    int j = 2;
    while (a[i] != '\0')
    {
        resStr[j++] = a[i];
        i++;
    }
    resStr[j++] = '+';
    i = 0;
    while (b[i] != '\0')
    {
        resStr[j++] = b[i];
        i++;
    }
    resStr[j++] = ')';
    resStr[j++] = '\'';
    resStr[j++] = ')';
    resStr[j++] = '\'';
    resStr[j] = '\0';
    return insert(ans, resStr);
}

char *evaluateAND(char *a, char *b)
{
    char resStr[100];
    resStr[0] = '(';
    int i = 0;
    int j = 1;
    while (a[i] != '\0')
    {
        resStr[j++] = a[i];
        i++;
    }
    j--;
    if (resStr[j] == '\'')
    {
    }
    else
    {
        j++;
        resStr[j++] = '\'';
    }
    resStr[j++] = '+';
    i = 0;
    while (b[i] != '\0')
    {
        resStr[j++] = b[i];
        i++;
    }
    j--;
    if (resStr[j] == '\'')
    {
    }
    else
    {
        j++;
        resStr[j++] = '\'';
    }
    resStr[j++] = ')';
    resStr[j++] = '\'';
    resStr[j] = '\0';
    return insert(ans, resStr);
}

char *insertChar(char c)
{
    char resStr[2];
    resStr[0] = c;
    resStr[1] = '\0';
    return insert(ans, resStr);
}

char *eval(struct ast *a)
{
    char *str;
    // calculated value of this subtree
    switch (a->nodetype)
    {
    case 'K':
        str = insertChar(((struct charval *)a)->c);
        break;
    case '+':
        str = evaluateOR(eval(a->l), eval(a->r));
        break;
    case '.':
        str = evaluateAND(eval(a->l), eval(a->r));
        break;
    default:
        printf("internal error: bad node %c\n", a->nodetype);
    }
    return str;
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
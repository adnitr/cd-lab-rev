/* calculator with AST */
%{
# include <stdio.h>

char NON[2][50];
int rowNON=0;

char *insertNON(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        NON[rowNON % 2][i] = s[i];
    }
    int temp = (rowNON % 2);
    rowNON++;
    return NON[temp];
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

char *evalK_NON(char c)
{
    char resStr[2];
    resStr[0] = c;
    resStr[1] = '\0';
    return insertNON(resStr);
}

%}

%token CHAR 
%token EOL
%left OR
%left AND

%%
calclist: /* nothing */
| calclist exp EOL { printf("Hi, I am root\n");}
;

exp: factor
| exp OR factor { printf("OR\n"); }
;

factor: term
| factor AND term {printf("AND\n");}
;

term: CHAR { printf("CHAR\n"); }
;
%%

int main(int argc, char **argv)
{
yyparse();
}
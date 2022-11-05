#include <stdio.h>

struct strset
{
    char *s1;
    char *s2;
};

void printString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

char NAN[50][50]; // NAND and NOT
char NON[50][50]; // NAND and NOT
int rowNAN = 0, rowNON = 0;

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

struct strset eval(char *a, char *b)
{
    char *s1 = evalOR_NON(a, b);
    char *s2 = evalOR_NAN(a, b);
    struct strset s;
    s.s1 = s1;
    s.s2 = s2;
    return s;
}

int main()
{

    struct strset s = eval("x", "y");
    printString(s.s1);
    printString(s.s2);
    // char *s1 = evalOR_NAN("a", "b");
    // char *s2 = evalOR_NON("a", "b");
    // char *s3 = evalAND_NAN("a", "b");
    // char *s4 = evalAND_NON("a", "b");
    // char *s5 = evalK_NAN('z');
    // char *s6 = evalK_NON('z');

    // printString(s1);
    // printString(s2);
    // printString(s3);
    // printString(s4);
    // printString(s5);
    // printString(s6);
}
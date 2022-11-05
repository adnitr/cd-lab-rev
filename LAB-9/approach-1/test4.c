#include <stdio.h>

void printString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
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
        i++;
    }
    i--;

    int st, en, not ;

    if (a[i] == '\'' && a[i - 1] == ')')
    {
        st = 1;
        en = i - 1;
        not = 0;
    }
    else if (a[i] == '\'')
    {
        st = 0;
        en = i;
        not = 0;
    }
    else
    {
        st = 0;
        en = ++i;
        not = 1;
    }

    for (int x = st; x < en; x++)
    {
        resStr[ptr++] = a[x];
    }

    if (not )
    {
        resStr[ptr++] = '\'';
    }

    resStr[ptr++] = '.';

    i = 0;
    while (b[i] != '\0')
    {
        i++;
    }
    i--;

    if (b[i] == '\'' && b[i - 1] == ')')
    {
        st = 1;
        en = i - 1;
        not = 0;
    }
    else if (a[i] == '\'')
    {
        st = 0;
        en = i;
        not = 0;
    }
    else
    {
        st = 0;
        en = ++i;
        not = 1;
    }

    for (int x = st; x < en; x++)
    {
        resStr[ptr++] = b[x];
    }

    if (not )
    {
        resStr[ptr++] = '\'';
    }

    resStr[ptr++] = ')';
    resStr[ptr++] = '\'';
    resStr[ptr] = '\0';

    printString(resStr);
}

int main()
{
    evalOR_NAN("(a+b)'", "b");
    return 0;
}
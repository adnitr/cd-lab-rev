#include <stdio.h>

void printString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

char ans[100][50]; // Table-1 from row-0 to row-49 && Table-2 from row-50 to row-99
int row1 = 0;
int row2 = 50;

int insertOne(char carr[][50], char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        carr[row1][i] = s[i];
    }

    return row1++;
}

int insertTwo(char carr[][50], char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        carr[row2][i] = s[i];
    }

    return row2++;
}

int evaluateOR(char *a, char *b)
{
    char resStr1[50];
    char resStr2[50];

    int ptr1 = 0, ptr2 = 0;

    // for table-1 --- a+b => ((a+b)')'
    // for table-2 --- a+b => (a'.b')'
    resStr1[ptr1++] = '(';
    resStr1[ptr1++] = '(';
    resStr2[ptr2++] = '(';

    int i = 0;
    while (a[i] != '\0')
    {
        resStr1[ptr1++] = a[i];
        resStr2[ptr2++] = a[i];
        i++;
    }

    resStr1[ptr1++] = '+';
    resStr2[ptr2++] = '\'';
    resStr2[ptr2++] = '.';

    i = 0;
    while (b[i] != '\0')
    {
        resStr1[ptr1++] = b[i];
        resStr2[ptr2++] = b[i];
        i++;
    }

    resStr1[ptr1++] = ')';
    resStr1[ptr1++] = '\'';
    resStr1[ptr1++] = ')';
    resStr1[ptr1++] = '\'';
    resStr1[ptr1] = '\0';

    resStr2[ptr2++] = '\'';
    resStr2[ptr2++] = ')';
    resStr2[ptr2++] = '\'';
    resStr2[ptr2] = '\0';

    insertOne(ans, resStr1);
    return insertTwo(ans, resStr2);
}

int evaluateAND(char *a, char *b)
{
    char resStr1[50];
    char resStr2[50];

    int ptr1 = 0, ptr2 = 0;

    // for table-1 --- a.b => (a'+b')'
    // for table-2 --- a.b => ((a.b)')'
    resStr1[ptr1++] = '(';
    resStr2[ptr2++] = '(';
    resStr2[ptr2++] = '(';

    int i = 0;
    while (a[i] != '\0')
    {
        resStr1[ptr1++] = a[i];
        resStr2[ptr2++] = a[i];
        i++;
    }

    resStr2[ptr2++] = '.';
    resStr1[ptr1++] = '\'';
    resStr1[ptr1++] = '+';

    i = 0;
    while (b[i] != '\0')
    {
        resStr1[ptr1++] = b[i];
        resStr2[ptr2++] = b[i];
        i++;
    }

    resStr2[ptr2++] = ')';
    resStr2[ptr2++] = '\'';
    resStr2[ptr2++] = ')';
    resStr2[ptr2++] = '\'';
    resStr2[ptr2] = '\0';

    resStr1[ptr1++] = '\'';
    resStr1[ptr1++] = ')';
    resStr1[ptr1++] = '\'';
    resStr1[ptr1] = '\0';

    insertOne(ans, resStr1);
    return insertTwo(ans, resStr2);
}

int main()
{
    int x = evaluateOR("a", "b");
    int y = evaluateAND("a", "b");

    printString(ans[x - 50]);
    printString(ans[x]);
    printString(ans[y - 50]);
    printString(ans[y]);
}
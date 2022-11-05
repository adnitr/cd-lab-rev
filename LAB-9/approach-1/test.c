#include <stdio.h>

// int row = 0;

// char *insert(char carr[][10], char *s)
// {
//     for (int i = 0; s[i] != '\0'; i++)
//     {
//         carr[row][i] = s[i];
//     }
//     int temp = row++;
//     return carr[temp];
// }

void printString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
    }
    printf("\n");
}

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
    resStr[j++] = '\'';
    resStr[j++] = '+';
    i = 0;
    while (b[i] != '\0')
    {
        resStr[j++] = b[i];
        i++;
    }
    resStr[j++] = '\'';
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

int main()
{
    // char carr[10][10];
    // char *cptr = insert(carr, "ADARSHING");
    // printString(cptr);
    char *st1 = evaluateOR("a", "b");
    char *st2 = evaluateAND("x", "y");
    char c = 'V';
    char *st3 = insertChar(c);
    printString(st1);
    printString(st2);
    printString(st3);
}
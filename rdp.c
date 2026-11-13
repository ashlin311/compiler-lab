#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void E();
void Edash();
void F();
void T();
void Tdash();

int i = 0;
char s[100];

void error()
{
    printf("INVALID EXPRESSION");
    exit(1);
}

void E()
{
    T();
    Edash();
}

void Edash()
{
    if (s[i] == '+')
    {
        i++;
        T();
        Edash();
    }
}

void T()
{
    F();
    Tdash();
}

void Tdash()
{
    if (s[i] == '*')
    {
        i++;
        F();
        Tdash();
    }
}

void F()
{
    if (s[i] == '(')
    {
        i++;
        E();

        if (s[i] == ')')
        {
            i++;
        }
        else
        {
            error();
        }
    }

    if (s[i] == 'i' && s[i + 1] == 'd')
    {
        i = i + 2;
    }
    else
    {
        error();
    }
}

void main()
{
    printf("ENTER EXPRESSION : ");
    scanf("%s", s);

    E();

    if (s[i] == '\0')
    {
        printf("STRING ACCEPTED");
    }
    else
    {
        printf("STRING REJECTED");
    }
}
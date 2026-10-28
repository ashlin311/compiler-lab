#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define LEN 256

char lhs[MAX][LEN], rhs[MAX][LEN];
char var[MAX][LEN], val[MAX][LEN];
int known[MAX], count = 0;

int isNumber(const char s[])
{
    char *end;

    if (s[0] == '\0')
        return 0;

    strtoll(s, &end, 10);

    return end != s && *end == '\0';
}

int find(const char name[])
{
    int i;

    for (i = 0; i < count; i++)
        if (strcmp(var[i], name) == 0)
            return i;

    return -1;
}

void propagate(char operand[])
{
    int i = find(operand);

    if (i != -1 && known[i])
        strcpy(operand, val[i]);
}

void update(const char name[], const char value[])
{
    int i = find(name);

    if (i == -1)
    {
        i = count++;
        strcpy(var[i], name);
    }

    if (isNumber(value))
    {
        strcpy(val[i], value);
        known[i] = 1;
    }
    else
        known[i] = 0;
}

void fold(char expression[], char output[])
{
    int pos = -1;
    char first[LEN], second[LEN], op;
    long long a, b, result;

    for (int i = 1; expression[i]; i++)
    {
        if (expression[i] == '+' || expression[i] == '-' ||
            expression[i] == '*' || expression[i] == '/')
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        strcpy(first, expression);
        propagate(first);
        strcpy(output, first);
        return;
    }

    op = expression[pos];
    expression[pos] = '\0';
    strcpy(first, expression);
    strcpy(second, expression + pos + 1);
    propagate(first);
    propagate(second);

    if (!isNumber(first) || !isNumber(second))
    {
        snprintf(output, LEN, "%s %c %s", first, op, second);
        return;
    }

    a = strtoll(first, NULL, 10);
    b = strtoll(second, NULL, 10);

    if (op == '/' && b == 0)
    {
        snprintf(output, LEN, "%s / %s", first, second);
        return;
    }

    switch (op)
    {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        default:  result = a / b; break;
    }

    snprintf(output, LEN, "%lld", result);
}

int main(void)
{
    int n, i, ch;
    char line[LEN], expr[LEN];
    char *eq;

    printf("Enter the number of expressions: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("Invalid number of expressions.\n");
        return 1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    printf("Enter the expressions:\n");

    for (i = 0; i < n; i++)
    {
        if (scanf("%255s", line) != 1)
            return 1;

        eq = strchr(line, '=');

        if (eq == NULL || eq == line || eq[1] == '\0')
        {
            printf("Invalid assignment.\n");
            return 1;
        }

        *eq = '\0';

        strcpy(lhs[i], line);
        strcpy(expr, eq + 1);

        fold(expr, rhs[i]);
        update(lhs[i], rhs[i]);
    }

    printf("\nOptimized code:\n");

    for (i = 0; i < n; i++)
        printf("%s = %s\n", lhs[i], rhs[i]);

    return 0;
}
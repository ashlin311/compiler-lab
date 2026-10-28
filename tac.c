#include <stdio.h>
#include <string.h>
#include <ctype.h>

int precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(const char infix[], char postfix[])
{
    char stack[50];
    int top = -1, k = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        if (isalnum(c))
        {
            postfix[k++] = c;
        }
        else if (c == '(')
        {
            stack[++top] = c;
        }
        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[k++] = stack[top--];
            }

            if (top != -1)
            {
                top--;
            }
        }
        else
        {
            while (top != -1 &&
                   precedence(stack[top]) >= precedence(c))
            {
                postfix[k++] = stack[top--];
            }

            stack[++top] = c;
        }
    }

    while (top != -1)
    {
        postfix[k++] = stack[top--];
    }

    postfix[k] = '\0';
}

int main(void)
{
    char exp[50], postfix[50];
    char *eq;

    printf("ENTER EXPRESSION (e.g., x=a+b*c): ");
    scanf("%49s", exp);

    eq = strchr(exp, '=');

    if (eq == NULL)
    {
        printf("Invalid!\n");
        return 0;
    }

    *eq = '\0';
    infixToPostfix(eq + 1, postfix);

    printf("THREE ADDRESS CODE :\n");

    char tac_stack[50][10];
    int t_top = -1;
    int temp_count = 1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (isalnum(c))
        {
            tac_stack[++t_top][0] = c;
            tac_stack[t_top][1] = '\0';
        }
        else
        {
            char op2[10], op1[10];

            strcpy(op2, tac_stack[t_top--]);
            strcpy(op1, tac_stack[t_top--]);

            printf("t%d = %s %c %s \n",
                   temp_count, op1, c, op2);

            char temp_name[10];

            snprintf(temp_name, sizeof(temp_name), "t%d", temp_count++);
            strcpy(tac_stack[++t_top], temp_name);
        }
    }

    if (t_top >= 0)
    {
        printf("%s = %s \n", exp, tac_stack[t_top]);
    }

    return 0;
}

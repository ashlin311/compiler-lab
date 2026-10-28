#include <stdio.h>
#include <string.h>
#include <ctype.h>

char table[4][4] = {
    {'>', '<', '<', '>'}, // +
    {'>', '>', '<', '>'}, // *
    {'>', '>', 'e', '>'}, // i
    {'<', '<', '<', 'e'}  // $
};

int get_index(char c)
{
    if (c == '+') return 0;
    if (c == '*') return 1;
    if (c == 'i') return 2;
    if (c == '$') return 3;
    return -1;
}

int main()
{
    char stack[30], input[30];
    int top = 0, i = 0;

    stack[top] = '$';

    printf("ENTER INPUT : ");
    if (scanf("%29s", input) != 1)
        return 1;

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    printf("-----------------------------------------\n");

    while (1)
    {
        for (int k = 0; k <= top; k++)
        {
            printf("%c", stack[k]);
        }

        printf("\t\t");

        for (int k = i; input[k] != '\0'; k++)
        {
            printf("%c", input[k]);
        }

        printf("\t\t");

        char row_sym = stack[top];
        char col_sym = input[i];

        if (row_sym == '$' && col_sym == '$')
        {
            printf("ACCEPTED\n");
            break;
        }

        int r = get_index(row_sym);
        int c = get_index(col_sym);

        if (r == -1 || c == -1)
        {
            printf("ERROR: Invalid character\n");
            break;
        }

        if (table[r][c] == '<' || table[r][c] == '=')
        {
            stack[++top] = col_sym;
            i++;
            printf("SHIFT %c\n", col_sym);
        }
        else if (table[r][c] == '>')
        {
            char popped = stack[top];

            if (popped == 'i')
            {
                top--;
                printf("REDUCE i\n");
            }
            else if (popped == '+' || popped == '*')
            {
                top--;
                printf("REDUCE %c\n", popped);
            }
            else
            {
                printf("SYNTAX ERROR during reduction\n");
                break;
            }
        }
        else
        {
            printf("SYNTAX ERROR\n");
            break;
        }
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

#define LEN 10
#define SIZE 50

struct {
    char res[LEN];
    char op;
    char opnd1[LEN];
    char opnd2[LEN];
} tac[SIZE];

int num, i;

void three_address_code()
{
    printf("Enter the number of instructions: ");
    scanf("%d", &num);

    printf("Enter each instruction (Example: t1 = a + b)\n");

    for (i = 0; i < num; i++)
    {
        scanf("%s = %s %c %s",
              tac[i].res,
              tac[i].opnd1,
              &tac[i].op,
              tac[i].opnd2);
    }
}

void generate_assembly()
{
    for (i = 0; i < num; i++)
    {
        switch (tac[i].op)
        {
            case '+':
                printf("\nMOV AX, %s", tac[i].opnd1);
                printf("\nADD AX, %s", tac[i].opnd2);
                printf("\nMOV %s, AX\n", tac[i].res);
                break;

            case '-':
                printf("\nMOV AX, %s", tac[i].opnd1);
                printf("\nSUB AX, %s", tac[i].opnd2);
                printf("\nMOV %s, AX\n", tac[i].res);
                break;

            case '*':
                printf("\nMOV AX, %s", tac[i].opnd1);
                printf("\nMOV BX, %s", tac[i].opnd2);
                printf("\nMUL BX");
                printf("\nMOV %s, AX\n", tac[i].res);
                break;

            case '/':
                printf("\nMOV AX, %s", tac[i].opnd1);
                printf("\nMOV BX, %s", tac[i].opnd2);
                printf("\nXOR DX, DX");
                printf("\nDIV BX");
                printf("\nMOV %s, AX\n", tac[i].res);
                break;

            default:
                printf("\nInvalid operator: %c\n", tac[i].op);
        }
    }
}

int main()
{
    three_address_code();

    printf("\nEquivalent 8086 Assembly Code:\n");

    generate_assembly();

    return 0;
}

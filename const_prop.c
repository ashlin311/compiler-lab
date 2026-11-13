#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Var {
    char name;
    int value;
    int constant;
};

int main(void) {
    struct Var v[20];
    int n, i;
    char expr[100];

    printf("Enter number of variables: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter variable, value and constant(1/0): ");
        scanf(" %c %d %d", &v[i].name, &v[i].value, &v[i].constant);
    }

    printf("\nEnter expression: ");
    scanf("%99s", expr);

    printf("\nAfter Constant Propagation: ");

    for (i = 0; expr[i] != '\0'; i++) {
        int found = 0;

        for (int j = 0; j < n; j++) {
            if (expr[i] == v[j].name && v[j].constant) {
                printf("%d", v[j].value);
                found = 1;
                break;
            }
        }

        if (!found)
            printf("%c", expr[i]);
    }

    printf("\n");

    return 0;
}
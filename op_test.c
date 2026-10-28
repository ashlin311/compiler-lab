#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char table[4][4] = {
    {'>','<','<','>'},
    {'>','>','<','>'},
    {'>','>','e','>'},
    {'<','<','<','e'}
};

int get_index(char op){
    if (op == '+')
        return 0;
    else if (op == '*')
        return 1;
    else if (op == 'i')
        return 2;
    else if (op == '$')
        return 3;
    else
        return -1;
}

void main(){
    char input[20],stack[20];
    int top = 0,i=0;

    stack[top] = '$';

    printf("Enter input:\n");
    scanf("%s",input);

    printf("Operator Precedence Parse\n");
    printf("|STACK |\tINPUT |\tACTIONS |\n");
    while(1){
        for(int k = 0 ; k<=top;k++){
            printf("%c",stack[k]);
        }

        printf("\t");

        for(int k=i;input[k]!='\0';k++){
            printf("%c",input[k]);
        }

        printf("\t");

        char row_symb = stack[top];
        char col_symb = input[i];

        if(row_symb=='$' && col_symb=='$'){
            printf("ACCEPTED\n");
            break;
        }

        int r = get_index(row_symb);
        int c = get_index(col_symb);

        if(r==-1 || c==-1){
            printf("INVALID INPUT\n");
            break;
        }

        if(table[r][c] == '<'){
            stack[++top] = col_symb;
            i++;
            printf("SHIFT %c\n",col_symb);
        }
        else if(table[r][c] == '>'){
            char popped = stack[top];

            if(popped=='i' || popped=='+' || popped=='*'){
                top--;
                printf("REDUCE %c\n",popped);
            }
            else{
                printf("SYNTAX ERROR during reduction\n");
                break;
            }
        }
        else{
            printf("INVALID INPUT\n");
            break;
        }
    }

    
}
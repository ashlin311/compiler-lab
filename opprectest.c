#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int table[4][4] = {
    {'>','<','<','>'},
    {'>','>','<','>'},
    {'>','>','e','>'},
    {'<','<','<','e'}
};

int get_index(char op){
    switch(op){
        case '+':
            return 0;
            break;
        case '*':
            return 1;
        case 'i':
            return 2;
            break;
        case '$':
            return 3;
            break;
        default:
            return -1;
    }
}

void main(){
    char input[50],stack[50];
    int top = 0,i = 0;

    stack[top] = '$';

    printf("Enter input:\n");
    scanf("%s",input);


    printf("STACK\t|INPUT\t|ACTIONS\n");

    while(1){

        for(int k = 0 ; k<=top ; k++){
            printf("%c",stack[k]);
        }

        printf("\t");

        for(int k = i; input[k]!='\0' ; k++){
            printf("%c",input[k]);
        }

        printf("\t");

        char row_symb = stack[top];
        char col_symb = input[i];

        if(row_symb == '$' && col_symb == '$'){
            printf("ACCEPTED\n");
            break;
        }

        int r = get_index(row_symb);
        int c = get_index(col_symb);

        if(r==-1 || c==-1){
            printf("Invalid expression\n");
            break;
        }

        if(table[r][c] == '<'){
            stack[++top] = col_symb;
            i++;
            printf("SHIFT %c\n",col_symb);
        }

        else if(table[r][c] == '>'){
            char popped = stack[top];
            if(popped == '+' || popped == '*' || popped == 'i'){
                top-- ;
                printf("REDUCED %c\n",popped);
            }
            else{
                printf("Error while reducing\n");
                break;
            }
        }
        else{
            printf("INVALID EXPRESSION\n");
            break;
        }


    }

}
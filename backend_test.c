#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tac{
    char res[10];
    char op;
    char op1[10];
    char op2[10];
}codes[50];

int n;

void three_address_code(){
    printf("Enter number of expressions\n");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%s = %s %c %s",codes[i].res,codes[i].op1,&codes[i].op,codes[i].op2);
    }
}

void generate_8086(){

    for(int i = 0;i<n;i++){
        char op = codes[i].op;

        switch(op){
            case '+':
                printf("MOV AX, %s\n",codes[i].op1);
                printf("ADD AX, %s\n",codes[i].op2);
                printf("MOV %s, AX\n",codes[i].res);
                break;
            case '-':
                printf("MOV AX, %s\n",codes[i].op1);
                printf("SUB AX, %s\n",codes[i].op2);
                printf("MOV %s, AX\n",codes[i].res);
                break;
            case '*':
                printf("MOV AX, %s\n",codes[i].op1);
                printf("MOV BX, %s\n",codes[i].op2);
                printf("MUL BX\n");
                printf("MOV %s, AX",codes[i].res);
                break;
            case '/':
                printf("MOV AX, %s\n",codes[i].op1);
                printf("MOV BX, %s\n",codes[i].op2);
                printf("XOR DX, DX\n");
                printf("DIV BX\n");
                printf("MOV %s, AX",codes[i].res);
                break;
            default:
                printf("Invalid operator\n");
        }
        printf("\n");

    }

}

void main(){

    three_address_code();

    printf("8086 ASSEMBLY CODE\n");
    printf("\n");
    generate_8086();
}
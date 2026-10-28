#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int precedence(char op){
    switch(op){
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        default:
            return 0;
    }
}

void infixtopostfix(char infix[],char postfix[]){

    char stack[50];
    int top = -1;
    int k=0;

    for(int i=0;infix[i]!='\0';i++){
        
        char c = infix[i];

        if(isalnum(c)){
            postfix[k++] = c;
        }
        else if(c == '('){
            stack[++top] = c;
        }
        else if(c==')'){
            while(top!=-1 && stack[top]!='('){
                postfix[k++] = stack[top--];
            }

            if(top!=-1){
                top--;
            }
        }
        else{
            while(top!=-1 && precedence(stack[top])>=precedence(c)){
                postfix[k++] = stack[top--];
            }

            stack[++top] = c;
        }

    }

    while(top!=-1){
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';

}

void main(){
    char *eq;
    char exp[50];
    char postfix[50];
    char tac_stack[50][10];

    printf("Enter expression:\n");
    scanf("%s",exp);

    eq = strchr(exp,'=');

    *eq = '\0';
    infixtopostfix(eq+1,postfix);

    printf("Three Address Code\n");

    int t_top = -1;
    int temp_count = 1;

    for(int i=0;postfix[i]!='\0';i++){
        char c = postfix[i];

        if(isalnum(c)){
            tac_stack[++t_top][0] = c;
            tac_stack[t_top][1] = '\0';
        }
        else{
            char op1[10],op2[10];
            strcpy(op2,tac_stack[t_top--]);
            strcpy(op1,tac_stack[t_top--]);

            printf("t%d = %s %c %s\n",temp_count,op1,c,op2);

            char temp_var[10];
            snprintf(temp_var,sizeof(temp_var),"t%d",temp_count++);
            strcpy(tac_stack[++t_top],temp_var);
        }
    }
    if(t_top>-1){
            printf("%s = %s\n",exp,tac_stack[t_top]);
        }
}
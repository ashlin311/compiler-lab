%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *s);
%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'

%%
exp: exp '+' exp
   | exp '-' exp
   | exp '*' exp
   | exp '/' exp
   | '(' exp ')'
   | NUMBER
   | ID
   ;
%%

void yyerror(char *s)
{
    printf("INVALID ARITHMETIC EXPRESSION\n");
    exit(0);
}

int main()
{
    printf("Enter an arithmetic expression: ");

    if (yyparse() == 0)
        printf("VALID EXPRESSION\n");

    return 0;
}
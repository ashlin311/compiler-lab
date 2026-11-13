#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Var {
    char name;
    int value;
    int constant;
}v[20];

void main(){
    int n;
    char expr[100];
    printf("Enter number of variables:\n");
    scanf("%d",&n);
    printf("Enter variable name, value, constant(0/1)\n");
    for(int i=0;i<n;i++){
        scanf(" %c %d %d",&v[i].name,&v[i].value,&v[i].constant);
    }

    printf("Enter expression:\n");
    scanf("%s",expr);

    for(int i = 0;expr[i]!='\0';i++){
        int found = 0;

        for(int j = 0;j < n;j++){
            if(expr[i] == v[j].name && v[j].constant){
                printf("%d",v[j].value);
                found = 1;
                break;
            }
        }
        if(!found){
            printf("%c",expr[i]);
        }

    }
    printf("\n");

}
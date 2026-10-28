#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Quadruple {
    int op;
    char arg1[10];
    char arg2[10];
    char result[10];
}quads[10];

struct Triple {
    int op;
    char arg1[10];
    char arg2[10];
}trips[10];

struct Operator {
    int pos;
    char op;
}ops[10];

void process_operators();
void process_structures();


char expr[50];
int op_count = 0;
char temp_var = 'Z';

void main(){
    printf("--- QUADRUPLES & TRIPLES GENERATOR ---\n\n");
    printf("Enter a valid arithmetic expression: ");
    scanf("%s",expr);

    process_operators();
    process_structures();

}

void process_operators(){
    int i;

    for(i=0; expr[i]!='\0';i++){
        if(expr[i] == '*' || expr[i] == '/'){
            ops[op_count].pos = i;
            ops[op_count].op = expr[i];
            op_count++;
        }
    }

    for(i=0;expr[i]!='\0';i++){
        if(expr[i]=='+' || expr[i]=='-'){
            ops[op_count].pos = i;
            ops[op_count].op = expr[i];
            op_count++;
        }
    }

    for(i=0;expr[i]!='\0';i++){
        if(expr[i]=='='){
            ops[op_count].pos = i;
            ops[op_count].op = expr[i];
            op_count++;
        }
    }
}

void process_structures(){
    char quad_map[50][10];
    int trip_map[50];
    int len = strlen(expr);

    for(int i=0;i<len;i++){
        quad_map[i][0] = expr[i];
        quad_map[i][1] = '\0';
        trip_map[i] = -1;
    }

    for(int i=0;i<op_count;i++){
        int pos = ops[i].pos;
        char op = ops[i].op;

        int left = pos - 1;
        int right = pos + 1;

        while(left>=0 && quad_map[left][0]=='\0'){
            left--;
        }

        while(right<len && quad_map[right][0]=='\0'){
            right++;
        }

        if(left<0 || right>len){
            printf("Invalid Expression\n");
            return;
        }

        quads[i].op = op;
        trips[i].op = op;

        if(op=='='){
            strcpy(quads[i].arg1,quad_map[left]);
            strcpy(quads[i].arg2,"-");
            strcpy(quads[i].result,quad_map[right]);

            strcpy(trips[i].arg1,quad_map[left]);
            strcpy(trips[i].arg2,"-");
        }
        else{
            strcpy(quads[i].arg1,quad_map[left]);
            strcpy(quads[i].arg2,quad_map[right]);
            
            sprintf(quads[i].result,"%c",temp_var);

            if(trip_map[left] != -1){
                sprintf(trips[i].arg1,"(%d)",trip_map[left]);
            }
            else{
                strcpy(trips[i].arg1,quad_map[left]);
            }

            if(trip_map[right]!=-1){
                sprintf(trips[i].arg2,"(%d)",trip_map[right]);
            }
            else{
                strcpy(trips[i].arg2,quad_map[right]);
            }
        }

        if(op!='='){
            strcpy(quad_map[pos],quads[i].result);
            trip_map[pos] = i;
            temp_var--;
        }

        quad_map[left][0] = '\0';

        if(op!='='){
            quad_map[right][0] = '\0';
        }

    }

    printf("\n=== QUADRUPLES ===\n");
    printf("Index | Op | Arg1 | Arg2 | Result\n");
    printf("---------------------------------\n");

    for (int i = 0; i < op_count; i++) {
        printf("(%d)   | %c  | %-4s | %-4s | %-4s\n",
               i, quads[i].op, quads[i].arg1,
               quads[i].arg2, quads[i].result);
    }

    printf("\n=== TRIPLES ===\n");
    printf("Index | Op | Arg1 | Arg2\n");
    printf("-------------------------\n");

    for (int i = 0; i < op_count; i++) {
        printf("(%d)   | %c  | %-4s | %-4s\n",
               i, trips[i].op, trips[i].arg1,
               trips[i].arg2);
    }

}
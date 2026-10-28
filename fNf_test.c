#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char productions[50][50];
int visited_first[50],visited_follow[50];
char set[50];
int set_size,production_count;



void first(char c);
void follow(char c);

int is_nonterminal(char c){
    return isupper(c);
}

void add_to_set(char c){
    for(int i = 0;i<set_size;i++){
        if (set[i] == c){
            return;
        }
    }

    set[set_size++] = c;
}

void print_set(char name[],char c){

    printf("%s(%c) = {",name,c);
    for(int i = 0;i<set_size;i++){
        printf("%c",set[i]);
    }
    printf("}\n");

}

void first(char c){

    char ch = c;

    if(!is_nonterminal(c)){
        add_to_set(c);
        return;
    }

    if(visited_first[ch]==1){
        return;
    }

    visited_first[ch] = 1;

    for(int i = 0 ; i<production_count ; i++){
        if(productions[i][0] == c){
            if(!is_nonterminal(productions[i][2])){
                add_to_set(productions[i][2]);
            }
            else{
                first(productions[i][2]);
            }
        }
    }
    visited_first[ch] = 0;

}

void follow(char c){

    char ch = c;

    if(visited_follow[ch]==1){
        return;
    }
    
    visited_follow[ch] = 1;

    if(productions[0][0] == c){
        add_to_set('$');
    }

    for(int i = 0;i<production_count;i++){
        int len = strlen(productions[i]);
        for(int j = 2;j<len;j++){
            if(productions[i][j] == c){
                if(j+1<len){
                    char next = productions[i][j+1];
                    if(is_nonterminal(next)){
                        first(next);
                    }
                    else{
                        add_to_set(next);
                    }
                }
                else if(productions[i][0]!=c){
                    follow(productions[i][0]);
                }
            }
        }
    }

    visited_follow[ch] = 0;


}


void main(){

    int non_terminal = 0;
    char elements[50];
    int j = 0;

    printf("Enter number of productions:\n");
    scanf("%d",&production_count);

    for(int i=0;i<production_count;i++){
        scanf("%s",productions[i]);

        for(j=0;j<non_terminal;j++){
            if(elements[j] == productions[i][0]){
                break;
            }
        }

        if(j==non_terminal){
            elements[non_terminal++] = productions[i][0];
        }
    }

    printf("FIRST AND FOLLOW SETS\n");

    for(int i=0;i<non_terminal;i++){

        char c = elements[i];

        set_size = 0;
        memset(visited_first,0,sizeof(visited_first));
        first(c);

        printf("\n");
        print_set("FIRST",c);

        set_size = 0;
        memset(visited_follow,0,sizeof(visited_follow));
        follow(c);

        print_set("FOLLOW",c);

    }

}
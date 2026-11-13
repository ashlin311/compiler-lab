#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void first(char c);
void follow(char c);
void print_set(char name[50],char c);
int production_count;
char productions[50][50];
char set[50];
int visited_first[50],visited_follow[50];
int set_size;

int is_nonterminal(char c){
    return isupper(c);
}

void add_to_set(char c){
    for(int i = 0;i<set_size;i++){
        if(c == set[i]){
            return;
        }
    }

    set[set_size++] = c;
}

void print_set(char name[50],char c){
    printf("%s(%c) = {",name,c);
    for(int i = 0;i<set_size;i++){
        printf("%c ",set[i]);
    }
    printf("}\n");
}

void first(char c){

    char ch = c;

    if(!is_nonterminal(c)){
        add_to_set(c);
        return;
    }

    if(visited_first[ch] == 1){
        return;
    }

    visited_first[ch] = 1;

    for(int i = 0 ;i<production_count;i++){
        if(productions[i][0]==ch){
            if(!is_nonterminal(productions[i][2])){
                add_to_set(productions[i][2]);
            }
            else{
                first(productions[i][2]);
            }
    }

    visited_first[ch] = 0;
 }

}

void follow(char c){
    char ch = c;

    if(visited_follow[ch] == 1){
        return;
    }

    if(productions[0][0] == c){
        add_to_set('$');
    }

    for(int i = 0;i<production_count;i++){
        int len = strlen(productions[i]);
        for(int j=2;j<len;j++){
            if(productions[i][j] == ch){
                if(j+1<len){
                    char next = productions[i][j+1];
                    if(is_nonterminal(next)){
                        first(next);
                    }
                    else{
                        add_to_set(next);
                    }
                }
                else if(productions[i][0]!=ch){
                    follow(productions[i][0]);
                }
            }
        }
    }
    visited_follow[ch] = 0;
}




void main(){

    int non_terminals = 0;
    char elements[50];
    int j = 0;

    printf("Enter number of productions:\n");
    scanf("%d",&production_count);

    for(int i = 0;i<production_count;i++){
        scanf("%s",productions[i]);

        for(j = 0;j<non_terminals;j++){
            if(productions[i][0] == elements[j]){
                break;
            }
        }

        if(j==non_terminals){
            elements[non_terminals++] = productions[i][0]; 
        }
    }

    printf("FIRST AND FOLLOW SETS\n");

    for(int i=0;i<non_terminals;i++){

        char c = elements[i];

        set_size = 0;
        memset(visited_first,sizeof(visited_first),0);
        first(c);

        printf("\n");
        print_set("FIRST",c);

        set_size = 0;
        memset(visited_follow,sizeof(visited_follow),0);
        follow(c);

        printf("\n");
        print_set("FOLLOW",c);
        
    }



}
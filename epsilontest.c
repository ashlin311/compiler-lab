#include <stdio.h>
#include <stdlib.h>


int n;
int transitions[20][20];
int visited[20];


void episilonClosure(int state){
    visited[state] = 1;

    for(int i = 0 ; i < n ; i++){
        if(transitions[state][i]==8 && visited[i]==0){
            episilonClosure(i);
        }
    }

}

void main(){

    printf("Enter number of states:\n");
    scanf("%d",&n);

    printf("Enter transition matrix(8 - epsilon, 9 - no transition):\n ");
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            scanf("%d",&transitions[i][j]);
        }
    }

    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            visited[j] = 0;
        }

        episilonClosure(i);

        printf("Epsilon closure of Q%d : {",i);
        for(int j=0;j<n;j++){
            if(visited[j]==1){
                printf("Q%d ",j);
            }
        }

        printf(" }\n");
    }

}

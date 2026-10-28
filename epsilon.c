#include <stdio.h>

int n;
int transitions[20][20];
int visited[20];

void epsilonClosure(int state){
	visited[state] = 1;
	transitions[state][state] = 1;
	for(int i=0;i<n;i++){
		if(transitions[state][i] == 1 && visited[i] == 0){
			epsilonClosure(i);
		}
	}
	
	
}

void main(){
	printf("Enter number of states:\n");
	scanf("%d",&n);
	
	printf("Enter transition matrix:\n");
	for(int i = 0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&transitions[i][j]);
		}
	}
	
	
	for(int i = 0;i<n;i++){
		for(int j=0;j<n;j++){
			visited[j] = 0;
		}
		epsilonClosure(i);
		
		printf("EPSILON CLOSURE (Q%d) = {",i);
		
		for(int j=0;j<n;j++){
			if(visited[j]){
				printf("Q%d ",j);
			}
		}
		printf("}\n");
	}
	
	
}
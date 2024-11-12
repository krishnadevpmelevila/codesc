#include <stdio.h>
#include <ctype.h>
#include <strings.h>
int n;
char rules[100][100],firstset[100],symbol;
void addtoset(char set[100], char k){

	for(i=0; set[i]!='\0';i++){
		if(set[i]==k){
			return;
		}
	}
	set[i]=k;
	set[i+1]='\0';
}
void findfirst(char symbol, char firstset[]){
	for(int i=0;i<n;i++){
		if(symbol==rules[i][0]){
			if(islower(rules[i][3])){
				addtoset(firstset,rules[i][3]);
			}else{
				char tempset[100]="";
				findfirst(rules[i][3],tempset);
				for(int j=0; tempset[j]!='\0',j++;){
					addtoset(firstset,tempset[j]);
				}
			}
			
		}
	}
}
void main(){
	printf("Enter no.of rules: ");
	scanf("%d",&n);
	getchar();
	printf("Enter the rules: ");
	for(int i=0; i<n;i++){
		scanf("%s",rules[i]);
		getchar();
	}
	printf("Enter the grammer whose First/Follow to be found: ");
	scanf("%c",&symbol);
	findfirst(symbol,firstset);
	for(int i=0;firstset[i]!='\0',i++;){
		printf("\t%c",firstset[i]);
	}
	printf("\t}");
	
}


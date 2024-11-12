#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct {
	char op[10];
	char arg1[100];
	char arg2[100];
	char res[100];
}Exp;

Exp exp[100];
int n;
int prop(int n, Exp expr[100]){
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(strcmp(expr[j].arg1,expr[i].res)==0 && strcmp(expr[i].op,"=")==0){
				strcpy(expr[j].arg1,expr[i].arg1);
			}
			if(strcmp(expr[j].arg2,expr[i].res)==0 && strcmp(expr[i].op,"=")==0){
				strcpy(expr[j].arg2,expr[i].arg1);
			}	
		}
	}
}
void main(){
	printf("No of exp: ");
	scanf("%d",&n);
	printf("Enter expressions: \n");
	for(int i=0;i<n;i++){
		scanf("%s%s%s%s",exp[i].op,exp[i].arg1,exp[i].arg2,exp[i].res);
	}
	prop(n,exp);
	printf("PROPOGATED: \n");
	for(int i=0;i<n;i++){
		if(strcmp(exp[i].op,"=")!=0){
		printf("%s%s%s%s\n",exp[i].op,exp[i].arg1,exp[i].arg2,exp[i].res);
	}}
}

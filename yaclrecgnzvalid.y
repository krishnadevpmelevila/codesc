%{
#include <stdio.h>

#include <stdlib.h>

%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'

%%
input: expr '\n';
expr: expr '+' expr | expr '*' expr | expr '/' expr | expr '-' expr | NUMBER | ID | '(' expr ')' ;
%%

int main(){
	printf("Enter the input: ");
	yyparse();
	printf("Expression is valid");
	exit(0);
}

int yyerror(char *s){
	printf("Expression invalid ");
	exit(0);
}

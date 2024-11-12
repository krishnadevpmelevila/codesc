%{

#include <stdio.h>

%}

%%
a {printf("A");}
b {printf("B");}
c {printf("C");}
[A-Za-z] {printf("%c",yytext[0]);}
[^a-zA-Z] { printf("%s",yytext);}
%%

int main(){
	printf("Enter the text: ");
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}

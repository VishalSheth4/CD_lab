%{
#include<stdio.h>
int num=0;
%}
%%
[0-9] num++;
%%
int main(void) {
yyin= fopen("f.in","r");
yylex();
printf("\nTotal Numbers in the files: %d\n",num);
}
int yywrap(void) {
return 1;
}
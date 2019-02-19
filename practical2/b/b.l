%{
    #include<stdio.h>
%}

%%
[0-9]* fprintf(yyout,"%s\n",yytext);
%%

int yywrap() {
    return 1;
}

int main() {
    // yyin=fopen("index.html","r");
    yyout=fopen("output.txt","w");
    yylex();
    return 0;
}

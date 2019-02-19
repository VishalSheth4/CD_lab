%{
    #include<stdio.h>
    #include<stdlib.h>
    int a=0, b=0, c=0, d;
%}
%x COMMENT

%%
"//".*   {a++;}
"/*"     { BEGIN COMMENT; }
<COMMENT>"*/" {c++; BEGIN INITIAL; }
<COMMENT>.    ;
%%

int yywrap(){
    return 1;
}
void main(int argc,char *argv[]){
    yyin=fopen("in.c","r");
    yylex();
    printf("single line %d \nmultiline %d \n",a,c);
    d=a+c;
    printf("total %d \n",d);
}
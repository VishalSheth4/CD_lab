%{
    #include<stdio.h>
    #include<stdlib.h>
    int single_line=0, multi_line=0, total_lines;
%}
%x COMMENT

%%
"//".*   {single_line++;}
"/*"     { BEGIN COMMENT; }
<COMMENT>"*/" {multi_line++; BEGIN INITIAL; }
<COMMENT>.    ;
%%

int yywrap(){
    return 1;
}

void main(int argc,char *argv[]){
    // yyin = fopen("main.c", "r");
    yyin = fopen(argv[1], "r");
    yylex();

    printf("=========================================\n");
    printf("single line comments: %d \nmultiline comments:%d \n", single_line, multi_line);
    total_lines = single_line + multi_line;
    printf("total comments: %d \n", total_lines);
}

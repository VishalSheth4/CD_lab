/* Program to add line numbers 
to a given file*/
%{ 
int line_number = 1; // initializing line number to 1 
%} 

/* simple name definitions to simplify 
the scanner specification name 
definition of line*/
line .*\n	 

%% 
{line} { printf("%10d %s", line_number++, yytext); } 

%% 

int yywrap(){} 

int main(int argc, char*argv[]) 
{ 
// yyin as pointer of File type 
extern FILE *yyin; 

/* yyin points to the file in.c and opens it in read mode.*/
yyin = fopen("in.c","r"); 

yylex(); // The function that starts the analysis. 

return 0; 
} 

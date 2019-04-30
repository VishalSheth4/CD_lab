file="main.c"
lex problem.l && gcc lex.yy.c && ./a.out $file > output.txt 
cat output.txt | boxes -d parchment | lolcat

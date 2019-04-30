/*
Gahan Saraiya (18MCEC10)
Compiler Design LPW 
April 30, 2019

Problems for even roll number -

Write a LEX program to count number of comment lines in any C program.
*/
#include <stdio.h>

void generator(int *array, int n) {
    /*
    Array generator
    */
   int i;
   for (i=0; i<n; i++){
       array[i] = i*i;  // store square of index as array value
   }
}

int main() {
    // Valar Morgholis
    printf("%d\n", 5566); //number is very odd though
    return 0;
    // Valar dohairis
}

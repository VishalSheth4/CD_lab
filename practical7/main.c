#include<stdio.h>
#include<string.h>

char op[2], temp1[10], temp2[10], result[10];

void main(){
    FILE *fp1;
    fp1 = fopen("6.out", "r");
    printf("Intermediadte code in 3 addressable format are:\n");
    while(!feof(fp1)){
        fscanf(fp1, "%s%s%s%s", op, temp1, temp2, result);
        if(strcmp(op, " = ") == 0) { printf("\n%s%s%s", result, op, temp1);} 
        else {printf("\n%s = %s%s%s", result, temp1, op, temp2);}
    }
    fclose(fp1);
    fp1 = fopen("6.out", "r");
    printf("\n\nAssembly code Generated for the Specified Intermediate Code is: \n");
    while(!feof(fp1)) {
        fscanf(fp1, "%s%s%s%s", op, temp1, temp2, result);
        if(strcmp(op, "+") == 0) {
            printf("\nMOV R0, %s", temp1);
            printf("\nADD R0, %s", temp2);
            printf("\nMOV %s, R0", result);
        }
        if(strcmp(op, "*") == 0) {
            printf("\nMOV R0, %s", temp1);
            printf("\nMUL R0, %s", temp2);
            printf("\nMOV %s, R0", result);
        }
        if(strcmp(op, "-") == 0) {
            printf("\nMOV R0, %s", temp1);
            printf("\nSUB R0, %s", temp2);
            printf("\nMOV %s, R0", result);
        }
        if(strcmp(op, "/") == 0) {
            printf("\nMOV R0, %s", temp1);
            printf("\nDIV R0, %s", temp2);
            printf("\nMOV %s, R0", result);
        }
        if(strcmp(op, " = ") == 0) {
            printf("\nMOV R0, %s", temp1);
            printf("\nMOV %s, R0", result);
        }
    }
    fclose(fp1);
    printf("\n\n");
}

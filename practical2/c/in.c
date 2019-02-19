#include<stdio.h>

#define PI 3.1415

main() {
    int i, j;
    i = 5;
    for (j=0; j<i*i; j++){
        j = i+j;
    }
    int jarvis = PI * i * j;
    printf("%d", jarvis);
}

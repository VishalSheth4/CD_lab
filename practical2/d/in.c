#include<stdio.h>
// define pi for fun
#define PI 3.1415

main() {
    int i, j;
    // initialize i
    i = 5;
    for (j=0; j<i*i; j++){
        j = i+j;
    }
    /*
    this is some brainiac activity!!!! 
    */
    int jarvis = PI * i * j;  // this is algorithm to sink blackhole
    printf("%d", jarvis);
}

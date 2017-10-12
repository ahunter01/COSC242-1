#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void){

    double a, b, c, topscore;
    double largest = 0.0;
    int n, reg = 0;

    while (4 == scanf("%d%lg%lg%lg", &n, &a, &b, &c)) {
        if (a > b && a > c){
            topscore = a;
        } else if ( b > a && b > c) {
            topscore = b;
        } else {
            topscore = c;
        }

        if (topscore > largest) {
            largest = topscore;
            reg = n;
        }

    }

    printf("registration number: %d\n", reg);
    printf("with a top score of: %lg\n", largest);
    
    return EXIT_SUCCESS;
    
}

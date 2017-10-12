#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 5

int main (void){
    double a[ARRAY_SIZE];
    int reg[ARRAY_SIZE];
    int i = 0, win = 0, n = 0;
    double s1 = 0.0, s2 = 0.0, s3 = 0.0, high = 0.0;
    
    while (4 == fscanf(stdin, "%d%lg%lg%lg", &n, &s1, &s2, &s3)) {
        reg[i] = n;
        if (s1 < s2 && s1 < s3) {
            a[i] = ((s2 + s3) / 2);
        }else if (s2 < s1 && s2 < s3) {
            a[i] = ((s1 + s3) / 2);
        }else {
            a[i] = ((s2 + s1) / 2);
        }
        i++;
    }
    high = a[0];
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (high <= a[i]) {
            high = a[i];
            win = reg[i];
        }
    }
    fprintf(stdout, "%d\n", win);
        
        
    return EXIT_SUCCESS;
}

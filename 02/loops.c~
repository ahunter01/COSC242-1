#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void){

    double s1, s2, s3;
    int return_code;
    printf("please enter 3 doubles:");
    fflush(stdout);
    return_code = scanf("%lg%lg%lg", &s1, &s2, &s3);

    printf("your inputs were: %lg, %lg, %lg\n", s1, s2, s3);

    if (s1 < s2 && s1 < s3){
        printf("%lg\n", (s2+s3)/2);
    }
    else if (s2 < s1 && s2 < s3){
        printf("%lg\n", (s1+s3)/2);
    } else {
        printf("%lg\n", (s1+s2)/2);
    }

    return EXIT_SUCCESS;
    
}

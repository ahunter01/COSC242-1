#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {

    int i = 0;
    int num = 0;

    num = atoi(argv[1]);

    for (i = 0; i < num; i++) {
        printf("%d\n", rand());
    }   
    
    return EXIT_SUCCESS;
}

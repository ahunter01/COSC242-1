#include <stdio.h>

int is_prime(int candidate) {
    int n = 2;
    int r = 0;
    
    for (n = 2; n < candidate; n++) {
        r = candidate % n;
        if (r == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int candidate = 2;
    int num_printed = 0;
    
    while (num_printed < 200) {
        if (is_prime(candidate)) {
            if ((num_printed % 10) == 0 && num_printed != 0){
                fprintf(stdout, "\n");
                }
            fprintf(stdout, "%5d", candidate);
            num_printed++;
        }
        candidate++;
    }
    fprintf(stdout, "\n");
    return 0;
}

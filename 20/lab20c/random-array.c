#include <stdio.h>
#include <stdlib.h>

void display_repeats(int a[], int n) {
    int i = 0, size = 0, count = 0;
    int *r;

    r = malloc(n * sizeof r[0]);
    while (size < n) {
        count = 0;
        for (i = 0; i < n; i++) {
            if (size == a[i]) {
                count++;
            }
        }
        r[size] = count;
        size++;
        
    }
    for (i = 0; i < n; i++) {
        if (r[i] >= 2) {
            fprintf(stdout, "%d occurs %d times\n", i, r[i]);
        }
    }
}
    
int main (void) {
    int array_size = 0;
    int *my_array;
    int i = 0;

    fprintf(stdout, "Enter the size of the array:\n");
    fscanf(stdin, "%d", &array_size);

    my_array = malloc(array_size * sizeof my_array[0]);
    if (NULL == my_array) {
        fprintf(stderr, "Memory allocation failed!\n");
        return EXIT_FAILURE;
    }
    
    /*fprintf(stdout, "What's in the array:\n");*/
    for (i = 0; i < array_size; i++) {
        my_array[i] = rand() % array_size;
        fprintf(stdout, "%d ", my_array[i]);
    }

    /*fprintf(stdout, "What's in the array:\n");
    for (i = 0; i < array_size; i++) {
        fprintf(stdout, "%d ", my_array[i]);
        }*/
    fprintf(stdout, "\n");
    
    display_repeats(my_array, array_size);

    free(my_array);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/* function to sort the array of data. */
void  insertion_sort(int *a, int n) {
    int p = 0;
    int key = 0;
    int temp = 0;
    for (p = 1; p < n; p++) {
        key = p;
        while (key > 0 &&  a[key] < a[key -1]) {
            temp = a[key];
            a[key] = a[key-1];
            a[key-1] = temp;
            key--;
        }
    }
}

int main (void) {
    int my_array[ARRAY_MAX];
    int i = 0;
    int count = 0;
    clock_t start, end;
    
    /* create the numbers to be sorted. */
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    
    /* clock is used to see the time of the function run. */
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    /* print out the sorted array. */
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    
    /* sends timing info to the standard error stream. */
    fprintf(stderr, "%d %f\n", count, (end - start)/(double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}

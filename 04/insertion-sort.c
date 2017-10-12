#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 30000
/* sorts through an array making it in order
   @param int a is the array
   @param int n is the length of the array
   returns an array in order */
void insertion_sort(int *a, int n) {
    int p, key, left;
    /*for each position p in array a except the first pull out the item at p
      and store it in the variable key */
    for (p = 1; p < n; p++) {
        key = a[p];
        left = p-1;

        /* move each item that is to the left  positoin p, and is greater
           than the key one place to the right put key in the leftmost pos */
        while (left >= 0 && a[left] > key) {
            a[left+1] = a[left];
            left--;
        }
        a[left+1] = key;
    }
}

int main(void) {
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;


    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

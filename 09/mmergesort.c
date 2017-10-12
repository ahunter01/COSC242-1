#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 2000000
int my_array[ARRAY_MAX];
int workspace[ARRAY_MAX];

void merge(int *array, int *workspace, int len) {
    int i = 0;
    int j = len / 2;
    int k = 0;

    while (i < (len / 2) && j < len) {
        if (array[i] < array[j]) {
            workspace[k] = array[i];
            i++;
        }else {
            workspace[k] = array[j];
            j++;
        }
        k++;
    }
    
    while (i < len/2) {
        workspace[k] = array[i];
        i++;
        k++;
    }
    while (j < len) {
        workspace[k] = array[j];
        j++;
        k++;
    }
}

/* function to sort the array of data. */
void merge_sort(int *a, int *w, int n) {
    int p = 0;
    if (n < 2) {
        return;
    }
    merge_sort(a, w, (n / 2));
    merge_sort((a + (n / 2)), w, n -( n / 2));
    
    merge(a, w, n);
    
    for (p = 0; p < n; p++){
        a[p] = w[p];
    }
}

int main (void) {
    
    int i = 0;
    int count = 0;
    clock_t start, end;
    
    /* create the numbers to be sorted. */
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    start = clock();
    merge_sort(my_array, workspace, count);
    end = clock();
    
    /* print out the sorted array. */
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    /* sends timing info to the standard error stream. */
    fprintf(stderr, "%d %f\n", count, (end - start)/(double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}

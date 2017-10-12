#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 30000
/*sorts through an array making it in order
  @param int a is the array
  @param int n the the length of the array
   returns an array in order*/
void selection_sort(int *a, int n) {
    int count, p, smallest, temp;
    /*for each position p in the array a except the last one 
      find the smallest item from position p to position (n - 1) */
    for (p = 0; p < n -1; p ++){
        smallest = p;
        for (count = p+1; count < n; count++){
            if (a[count] < a[smallest]) {
                smallest = count;
            }
        }
        /*swap the item you find with whatever is at position p right now */
        temp = a[smallest];
        a[smallest] = a[p];
        a[p] = temp;
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
    selection_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end-start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

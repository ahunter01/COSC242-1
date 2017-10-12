#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
  int capacity;
  int itemcount;
  int *items;
};
void  selection_sort(int *a, int n) {
    int p = 0;
    int i = 0;
    int smallest  = 0;
    int temp = 0;
    for (p = 0; p < (n-1); p++) {
        smallest = p;
        for (i = p+1; i < n; i++) {
            if (a[smallest] > a[i]) {
                smallest = i;
            }
        }
        if (smallest != p) {
            temp = a[p];
            a[p] = a[smallest];
            a[smallest] = temp;
        }
        if (p == ((n / 2) - 1)) {
            for (i = 0; i < n; i++) {
                fprintf(stderr, "%d\n", a[i]);
            }
        }
    }
}

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    p = realloc(p, s);
    if (NULL == p) {
        fprintf(stderr, "Memory realocation failed!");
        exit(EXIT_FAILURE);
    }
    return p;
}

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity / sizeof result ->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
  if (f->itemcount == f->capacity) {
      f->capacity += f->capacity;
      f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
  }
  f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    int i;

    for (i = 0; i < f->itemcount; i++) {
        fprintf(stdout, "%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f) {
    selection_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}

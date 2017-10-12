#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

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

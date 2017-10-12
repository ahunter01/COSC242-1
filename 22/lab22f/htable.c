#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};

htable htable_new(int capacity) {
    int i = 0;
    htable result = emalloc(sizeof *result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    for (i = 0; i < result->capacity; i++) {
        result->keys[i] = NULL;
    }
    return result;
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str) {
    int num = htable_word_to_int(str) % h->capacity;
    int col = 0;
    
    while (col < h->capacity) {
        if (NULL == h->keys[num]) {
            h->keys[num] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
            strcpy(h->keys[num], str);
            h->num_keys++;
            return 1;
        }
        if (strcmp(h->keys[num], str) == 0) {
            return 0;
        }
        col++;
        num = (num + 1) % h->capacity;
    }
   
}

void htable_print(htable h, FILE *stream) {
    int i;

    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}

void htable_free(htable h) {
    int i = 0;
    for (i = 0; i < h->capacity; i++) {
        free(h->keys[i]);
    }
    free(h->keys);
    free(h);
}


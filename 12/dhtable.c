#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequency;
    char **keys;
};

htable htable_new(int capacity){
    int i = 0;

    /*declare a htable and allocate memory as appropriate.*/
    htable result = emalloc(sizeof *result);

    /*initialise the htable's capacity and number of keys appropriately.*/
    result->capacity = capacity;
    result->num_keys = 0;

    /*allocate htable's frequency array to be able to store enough integers.*/
    result->frequency = emalloc(result->capacity * sizeof result->frequency[0]);

    /*allocate htable's keys array to be able to store enough strings */
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);

    /*set each frequency and key to their initial values.*/
    for (i = 0; i < result->capacity; i++) {
        result->keys[i] = NULL;
        result->frequency[i] = 0;
    }

    /*return the hash table.*/
    return result;
}

void htable_free(htable h){
    free(h->keys);
}

/*Convets a string to an integer*/
static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}

int htable_insert(htable h, char *str){
    int num = htable_word_to_int(str) % h->capacity;
    int col = 0;
    int step = htable_step(h, num);
    
    while (col < h->capacity) {
        /*
         * If there is no string at that position, copy the string to that 
         * position and set the cell in the frequency array to 1.
         * Increment the number of keys and return 1.
         */
        if (NULL == h->keys[num]) {
            h->keys[num] = emalloc((strlen(str) + 1) * sizeof h->keys[0]);
            strcpy(h->keys[num], str);
            h->num_keys++;
            h->frequency[num] = h->frequency[num] + 1;
            return 1;
        }
        /*
         * If the same string is at that position, increment the frequency
         * at that position and returnt the frequency.
         */
        if (strcmp(h->keys[num], str) == 0) {
            h->frequency[num] = h->frequency[num] + 1;
            return h->frequency[num];
        }
        num = (num + step) % h->capacity;
        col += step;
    }
    return 0; /*hash table must be full so return 0.*/
}


void htable_print(htable h, FILE *stream) {
    int i;

    for (i = 0; i < h->num_keys; i++) {
        if ('\0' != h->keys[i]) {
            fprintf(stream, "%d %s\n", h->frequency[i], h->keys[i]);
        }
    }
}

int htable_search(htable h, char *str){
    /*Creates, and initialises, a value to hold the number of collisions. */
    int col = 0;

    /*Calcute the position at which we should start looking for our key. */
    int p = htable_word_to_int(str) % h->capacity;
    int step = 0;

    /*While there is an item at that position, but isn't the key */
    while (NULL != h->keys[p] && strcmp(str, h->keys[p]) != 0
           && col < h->capacity) {
        p = (p + 1) % h->capacity; /*increment position to look in next cell.*/
        step = (p + (col * htable_step(h, p))) % h->capacity;
        col += step; /*increment collisions*/
    }
    /* If the number of collisions is equal to the capacity */
    if (col == h->capacity) {
        return 0; /* return 0 because hashtable full but did not contain key*/
    }else { 
        return h->frequency[p];/*else return the frequency at our final position */ 
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

#define IS_DOUBLE(x) (DOUBLE_H == (x)->method)

struct htablerac {
    int capacity;
    int num_keys;
    char **keys;
    int *freqs;
    int *stats;
    hashing_t method;
};

/*****************************************************************************
 * Function: htable_word_to_int
 * Input   : char *word
 * Output  : static unsigned int
 * Procedure: Performs linear hashing resolution strategy on the table.
 *****************************************************************************/

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while(*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}
/*****************************************************************************
 * Function: double_hash
 * Input   : int x, int c, htable h
 * Output  : static unsigned int
 * Procedure: Performs double hashing resolution strategy on the table.
 *****************************************************************************/

static unsigned int double_hash(int x, int c, htable h) {
    unsigned int result = 0;
    result = (x + c * (1 + x % (h->capacity - 1)))%h->capacity;
    return result;    
}

/*****************************************************************************
 * Function: htable_print_entire_table
 * Input   : htable h
 * Output  : void
 * Procedure: Prints the entire hashtable; index, frequency, stats and keys 
 *****************************************************************************/

void htable_print_entire_table(htable h) {
    int index = 0;
    fprintf(stderr, "%5s %5s %5s   %s\n", "Pos", "Freq", "Stats", "Word");
    fprintf(stderr, "----------------------------------------\n");
    while(index < h->capacity) {
        if(h->keys[index] != NULL){
        fprintf(stderr, "%5d %5d %5d   %s\n", index, h->freqs[index],
                h->stats[index], h->keys[index]);
        }else{
            fprintf(stderr, "%5d %5d %5d    \n", index, h->freqs[index],
                    h->stats[index]);
        }
        
        index++;
    }
}

/*****************************************************************************
* Function: htable_new
* Input   : int capacity, hashing_t hasht
* Output  : htable
* Procedure: Allocates memory to the tree; 
*****************************************************************************/

htable htable_new(int capacity, hashing_t hasht){
    int i;
    htable result = emalloc(sizeof *result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity* sizeof result->keys[0]);
    result->freqs = emalloc(result->capacity*
                            sizeof result->freqs[0]);
    result->stats = emalloc(result->capacity* sizeof result->stats[0]);
    result->method = hasht;
    for(i = 0;i < capacity; i++){
        result->keys[i] = NULL;
        result->freqs[i] = 0;
        result->stats[i] = 0;
    }

    return result;
}


/*****************************************************************************
 * Function: htable_free
 * Input   : htable h
 * Output  : void
 * Procedure: Traverse the table and free the memory allocated 
 * 			  including the keys, the frequencies the stats.
 *****************************************************************************/

void htable_free(htable h){
    int i;
    for(i = 0;i < h->num_keys;i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->freqs);
    free(h->stats);
    free(h);
}

/*****************************************************************************
 * Function: htable_insert
 * Input   : htable h, char *str
 * Output  : int
 * Procedure: Allocate memory for keys within a new hashtable
 *****************************************************************************/

int htable_insert(htable h, char *str){
    unsigned int i = htable_word_to_int(str);
    int i2 = 0;
    if(!IS_DOUBLE(h)) {
        while(i2 != h->capacity) {
            i = i % h->capacity;
            if(h->keys[i] == NULL){
                h->keys[i] = emalloc((strlen(str)+1) * sizeof str[0]);
                strcpy(h->keys[i], str);
                h->num_keys++;
                h->freqs[i]++;
                h->stats[i] = i2;
                return 1;
            }else if(strcmp(h->keys[i], str) == 0){
                return ++h->freqs[i];
            }else{
                i2++;
                i++;
            }
        }
    }else{
        while(i2 != h->capacity) {
            i = double_hash(i, i2, h);
            i = i % h->capacity;
            if(h->keys[i] == NULL){
                h->keys[i] = emalloc((strlen(str)+1) * sizeof str[0]);
                strcpy(h->keys[i], str);
                h->num_keys++;
                h->freqs[i]++;
                h->stats[i] = i2;
                return 1;
            }else if(strcmp(h->keys[i], str) == 0){
                return ++h->freqs[i];
            }else{
                i2++;
            }
        }
    }   
    return 0;
    
}

/*****************************************************************************
 * Function: htable_search
 * Input   : htable h, char *str
 * Output  : int
 * Procedure: Checks within the hashtable using double hashing and linear
			Returning 1 if the value is found, 0 if not;
 *****************************************************************************/

int htable_search(htable h, char *str){
    int coll = 0;
    unsigned int i = htable_word_to_int(str);
    if(!IS_DOUBLE(h)){
        while(coll < h->capacity){
            i = i % h->capacity;
            if(h->keys[i] != NULL && strcmp(h->keys[i], str) == 0){
                return 1;
            }else{
                coll++;
                i++;
            }
        }
        return 0;   
    }else{
        while(coll < h->capacity){
            i = double_hash(i, coll, h);
            i = i % h->capacity;
            if(h->keys[i] != NULL && strcmp(h->keys[i], str) == 0){
                return 1;
            }else{
                coll++;
                i++;
            }
        }
        return 0;
    }
    return 0;  
}

/*****************************************************************************
 * Function: htable_print
 * Input   : htable h, void f(int freq, char *str)
 * Output  : void
 * Procedure: Gathers the entire keys within the hashtable to capacity 
			  for use in printing.
 *****************************************************************************/

void htable_print(htable h, void f(int freq, char *str)) {
    int i;
    for (i = 0; i < h->capacity; i++){
        if(h->keys[i] != NULL){
            f(h->freqs[i], h->keys[i]);
        }
    }
}
/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
    fprintf(stream, "-----------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "-----------------------------------------------------\n\n");
}



  

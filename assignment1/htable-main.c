/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <math.h>
#include "htable.h"
#include "mylib.h"

/*setting the default hash table size to 113*/
#define HASHSIZE 113

/* check for a prime number>= table size to use as the table value*/
int is_prime(int num){
    if((num & 1)==0)
        return num == 2;
    else {
        int x, limit = sqrt(num);
        for (x = 3; x <= limit; x+=2){
            if (num % x == 0)
                return 0;
        }
    }
    return 1;
}

/* check for a prime number after the given value*/
int next_prime(int num){
    int x;
    if(num < 2)
        x = 2;
    else if (num == 2)
        x = 3;
    else if(num & 1){
        num += 2;
        x = is_prime(num) ? num : next_prime(num);
    } else
        x = next_prime(num-1);

    return x;
}




int main(int argc, char **argv) {
    htable t;
    int spellcheck, stats, printinfo, num_snaps,hashs;
    FILE *infile;
    char word[256];
    char option;
    clock_t start_f, start_s, end_f, end_s;
    double fill_t, search_t;
    int unknownCount;
    hashing_t hasht = LINEAR_P;

    const char *optstring ="c:deps:t:h";
    t = NULL;
    infile = NULL;
    hashs = 0;
    spellcheck = 0;
    printinfo = 0;
    stats = 0;
    num_snaps = 10;
    unknownCount = 0;
 	
	/* Handeling of specific cases inputed via the user on the file*/
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch(option) {
            case 'c':
                spellcheck = 1;
				/* attempt to open infile for spell check*/
                if(NULL == (infile = fopen(optarg, "r"))){
                    fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[optind]);
                    return EXIT_FAILURE;
                }
                stats = 2;
                break;
            case 'd':
                /* makes the hashing type double */
                hasht = DOUBLE_H;
                break;
            case 'e':
                /* prints the entire table */
                printinfo = 1;
                break;
            case 'p':
                /* prints the snapshots of the tables */
                stats = 1;
                break;
            case 's':
                /* sets the number of snaps shots */
                num_snaps = atoi(optarg);
                break;
            case 't':
               /*sets the table size to the next primenumber of that is given */
                hashs = next_prime(atoi(optarg));                          
                break;
            case 'h':
            default:
                printf("How to use this program: \n");
                printf("using -c command allows you to specify another file");
                printf(" to spell check against the first input file \n");
                printf("using -d makes the collision resolution strategy to ");
                printf("double hashing instead of the default\n");
                printf("using the -e command displays the entire contents of");
                printf(" the file\n");
                printf("using the -p command prints the tables stats, such as");
                printf(" the percentage of the table that is full, average ");
                printf("collisions and maximum collisions\n");
                printf("using the -s x displays upto the given number of ");
                printf("snaps shots of the table, if the table is not full, ");
                printf("fewer snapshots will be shown\n");
                printf("using the -t x command will find the first prime ");
                printf("number that is >= x and set the table size to x"); 
                break;       
        }
    }
    /* make new table and fill it from file; recording times
       for filling the table; close file */
    start_f = clock();
    if(hashs == 0){
        t = htable_new(HASHSIZE, hasht);
    }else{
        t = htable_new(hashs, hasht);
    }
        
    while(getword(word, sizeof word, stdin) != EOF) {
        if(htable_insert(t, word) == 0){
            fprintf(stderr, "hashtable is full");
        }
    }
    end_f = clock();
    if(spellcheck != 1 && printinfo != 1 && stats != 1){
        htable_print(t, print_info);
    }
	/* print if requested for all information*/
    if(printinfo == 1){
        htable_print_entire_table(t);
    }
	/* find words not in table and print them to stdout; record times for
           searching the table */
    if(spellcheck == 1){
        start_s = clock();
        while(getword(word, sizeof word, infile) != EOF) {
            if(htable_search(t, word) != 1){
                unknownCount++;
                fprintf(stdout, "%s\n", word);
            }
        }
        end_s = clock();
		/* calculate the time it took to fill and search */
        fill_t = ((end_f - start_f)/(double)CLOCKS_PER_SEC);
        search_t = ((end_s - start_s)/(double)CLOCKS_PER_SEC);
        
		/* print info*/
        fprintf(stderr, "Fill time     : %2.6f\n", fill_t);
        fprintf(stderr, "Search time   : %2.6f\n", search_t);
        fprintf(stderr, "Unknown words : %d\n", unknownCount); 
        stats = 0;
	/* print if requested for snapshots */
    }else if(stats  == 1){
        htable_print_stats(t, stdout, num_snaps);
    }
    
    /* frees the memory of the table */
    htable_free(t);
    return EXIT_SUCCESS;             
        
}



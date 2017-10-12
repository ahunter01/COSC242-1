/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include "tree.h"
#include "mylib.h"


int main(int argc, char **argv) {
    tree t;
    int spellcheck, rbt, outdot, depth;
    FILE *infile, *outfile;
    char word[256];
    char option;
    clock_t start_f, start_s, end_f, end_s;
    double fill_t, search_t;
    int unknownCount;

    const char *optstring ="c:df:orh";
    t = NULL;
    outfile = NULL;
    infile = NULL;
    spellcheck = 0;
    rbt = 0;
    outdot = 0;
    depth = 0;
    unknownCount = 0;
	
    while ((option = getopt(argc, argv, optstring)) != EOF) {

        switch(option) {
            case 'c':
                spellcheck = 1;
				/* attempt to open file */
                if(NULL == (infile = fopen(optarg, "r"))){
                    fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[optind]);
                    return EXIT_FAILURE;
                }
                depth = 2;
                outdot = 2;
                break;
            case 'd':
                /* sets the depth option to true */
                if(depth != 2){
                    depth = 1;
                }
                break;
            case 'f':
			
				/* attempt to open file */
                if(NULL == (outfile = fopen(optarg, "w"))){
                    fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[optind]);
                    return EXIT_FAILURE;
                }
   
                break;
            case 'o':
                /* sets the make tree-view.dot to true */
                if(outdot != 2){
                    outdot = 1;
                }
                break;
            case 'r':
                /* makes the tree a rbt instead of a bst */
                rbt = 1;
                break;
            case 'h':
            default:
                printf("How to use this program: \n");
                printf("using -c command allows you to specify another file");
                printf(" to spell check against the dictonary file \n");
                printf("using -d prints the depth of the tree made with the");
                printf(" dictonary file\n");
                printf("using the -f command allows you to specify another file");
                printf(" which writes the dot output to instead of the standard");
                printf(" file 'tree-view.dot\n");
                printf("using the -o outputs a representation of the tree in \"dot");
                printf("\" form to the file 'tree-view.dot' \n");
                printf("using the -r command makes the storage tree a rbt instead");
                printf(" of the standard bst tree format\n");
                break;
                   
        }
    }
	/* make new tree and fill it from file; record times; close file */
    start_f = clock();
    if(rbt == 1){
        t = tree_new(RBT);
    }else {
        t = tree_new(BST);
    }
    while(getword(word, sizeof word, stdin) != EOF) {
        t = tree_insert(t, word); 
    }
    t = root_fix(t);
    end_f = clock();
	
	/* print depth if requested; if this option is used, exit afterwards */
    if(depth == 1){
        fprintf(stdout, "depth of the tree is : %d\n", tree_depth(t) - 1);
        return EXIT_SUCCESS;
    }
	/* find words not in tree and print them to stdout; record times */
    if(spellcheck == 1){
        start_s = clock();
        while(getword(word, sizeof word, infile) != EOF) {
            if(tree_search(t, word) != 1){
                unknownCount++;
                fprintf(stdout, "%s\n", word);
            }
        }
        end_s = clock();
		
		/* calculate the time it took to fill and search */
        fill_t = ((end_f - start_f)/(double)CLOCKS_PER_SEC);
        search_t = ((end_s - start_s)/(double)CLOCKS_PER_SEC);
        
		/* print info as requested */
        fprintf(stderr, "\nStats:\n");
        fprintf(stderr, "Fill time     : %2.5f\n", fill_t);
        fprintf(stderr, "Search time   : %2.5f\n", search_t);
        fprintf(stderr, "Unknown words : %d\n", unknownCount); 
        outdot = 0;
		
	/* output the tree-view.dot file as requested */
    }else if(outdot == 1){
        if(outfile != NULL){
            tree_output_dot(t, outfile);
        }else{
            outfile = fopen("tree-view.dot", "w");
            tree_output_dot(t, outfile);
        }
    }
    tree_free(t);
    return EXIT_SUCCESS;             
        
}

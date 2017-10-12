#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_array(char **wordlist, int len, double average){
    if(len>0){
        if(strlen(wordlist[0])>average){
            printf("%s\n", wordlist[0]);
        }
        print_array(wordlist + 1, len-1, average);
    }
}

int main(void){
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words= 0;
    double average= 0.0;
    int i;

    while (num_words < ARRAY_LEN && 1 == scanf("%79s", word)) {
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof word[0]);
        strcpy(wordlist[num_words++], word);
        average += strlen(word);

    }
 

    if(num_words>0){
        average = average / num_words;
        fprintf(stderr,"%.2f\n", average);
        print_array(wordlist, num_words, average);

    }
    

    for(i = 0; i < num_words; i++){
        free(wordlist[i]);
    }

    

    return EXIT_SUCCESS;
}

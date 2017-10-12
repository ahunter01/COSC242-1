#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

/* fucntion that uses malloc to allocate new memory
 * PARAMS:
 *  size_t is the size of the thing to allocate memory for.
 */
extern void *emalloc(size_t);

/* reallocates memory using the realloc to do so
 * PARAMS:
 *  a void pointer to reallocate memor for.
 *  size_t is the size of the thing to reallocate memory for.
 */
extern void *erealloc(void *, size_t);

/* gets a word and transforms that word into an integer representative of it.
 * PARAMS:
 *  a char pointer for the word to be changed
 *  an int which shold be the max size a word can be.
 *  a pointer to a FILE stream
 * RETURN:
 *  returns the integer representation of a chosen word/
 */
extern int getword(char *, int, FILE *);

#endif

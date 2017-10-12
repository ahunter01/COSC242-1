#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>

typedef enum {BST, RBT} tree_t;
typedef enum {RED, BLACK } tree_colour;
typedef struct tree_node *tree;

extern tree root_fix(tree t);
extern tree tree_free(tree t);
extern void tree_inorder(tree t, void f(int freq, char *str));
extern tree tree_insert(tree t, char *str);
extern tree tree_new(tree_t t);
extern void tree_preorder(tree t, void f(int freq, char *str));
extern int tree_search(tree t, char *str);
extern tree right_rotate(tree t);
extern tree left_rotate(tree t);
extern tree tree_fix(tree t);
extern int tree_depth(tree t);
extern void tree_output_dot(tree t, FILE *out);

#endif

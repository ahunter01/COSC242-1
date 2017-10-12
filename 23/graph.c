#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"

typedef enum { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

/* create a graph struct. */
struct graphrec {
    int **edges;
    int *predecessor;
    int *distance;
    int *finish;
    state_t *state;
    int size;
};

/*static integer value used for the step in finish and graph_dfs/visit. */
static int step = 0;

/*
 * creates a new and initialised graph with int vertices. Performs the
 * memory allocation neccessary for the graph.
 * PARAMS: takes an integer to determine the number of nodes/vertices
 * the graph has.
 * RETURN: an initialised graph
 */
graph graph_new(int vertices) {
    int i;
    int j;
    graph result = emalloc(sizeof *result);
    result->size = vertices;
    result->edges = emalloc(result->size * sizeof result->edges[0]);
    result->finish = emalloc(result->size * sizeof result->edges[0]);
    result->predecessor = emalloc(result->size * sizeof result->predecessor[0]);
    result->distance = emalloc(result->size * sizeof result->distance[0]);
    result->state = emalloc(result->size * sizeof result->state[0]);
    for (i = 0; i < result->size; i++) {
        result->edges[i] = emalloc(result->size * sizeof result->edges[0][0]);
        result->predecessor[i] = 0;
        result->finish[i] = 0;
        result->distance[i] = 0;
        result->state[i] = UNVISITED;
        for (j = 0; j < result->size; j++) {
            result->edges[i][j] = 0;
        }
    }
    return result;
}

/* funciton adds values to the boolean matrix edges.
 * PARAMS: a grah g to add edges too.
 *         two integer values that are edges to each other (v1 and v2).
 */
void graph_add_edge(graph g, int v1, int v2) {
    g->edges[v1][v2] = 1;
}

/* recursive function used in graph_dfs in order to get the distance,
 * preecessor, state and finishing values for a vertex.
 * PARAMS: a graph g used from the graph_dfs.
 *         v is an integer value that is the vertex value to be used.
 */
static void visit(graph g, int v) {
    int u;
    g->state[v] = VISITED_SELF;
    step++;
    g->distance[v] = step;
    for (u = 0; u < g->size; u++) {
        if (g->edges[v][u] == 1 && g->state[u] == UNVISITED) {
            g->predecessor[u] = v;
            visit(g, u);
        }
    }
    step++;
    g->state[v] = VISITED_DESCENDANTS;
    g->finish[v] = step;
}

/* function that performs a breadth-first search on a graph.
 * PARAMS: a graph g for the bfs to be performed on.
 */
void graph_dfs(graph g) {
    int i;
    for (i = 0; i < g->size; i++) {
        g->state[i] = UNVISITED;
        g->predecessor[i] = -1;
    }
    step = 0;
    for (i = 0; i < g->size; i++) {
        if (g->state[i] == UNVISITED) {
            visit(g, i);
        }
    }
}

/* prints out which nodes are adjacent to eachother, a vertices distance
 * and predecessor.
 * PARAMS: a graph g that will be printed.
 */
void graph_print(graph g) {
    int i;
    int j = 0;
    int count = 0;
    printf("adjacency list:\n");
    for (i = 0; i < g->size; i++) {
        printf("%d | ", i);
        count = 0;
        for (j = 0; j < g->size; j++) {
            if (g->edges[i][j] == 1) {
                if (count == 0) {
                    printf("%d", j);
                    count++;
                }else {
                    printf(", %d", j);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("vertex distance pred finish\n");
    for (i = 0; i < g->size; i++) {
        printf("%4d %6d %6d %6d\n",
               i, g->distance[i], g->predecessor[i], g->finish[i]);
    }
}

/* frees a graph g and all its memory allocations.
 * PARAMS: a graph g to be freed.
 */
void graph_free(graph g) {
    int i;
    for (i = 0; i < g->size; i++) {
            free(g->edges[i]);
    }
    free(g->finish);
    free(g->predecessor);
    free(g->state);
    free(g->distance);
    free(g->edges);
    free(g);
}

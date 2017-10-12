#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct graphrec *graph;

extern void graph_print(graph g);
extern graph graph_new(int vertices);
extern void graph_free(graph g);
extern void graph_add_edge(graph g, int v1, int v2);
extern void graph_bfs(graph g, int source);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"
#include "queue.h"

int main(void) {
    int u = 0, v = 0;
    int vertices = 0;
    graph g;

    scanf("%d", &vertices);
    g = graph_new(vertices);

    while (2 == scanf("%d%d", &u, &v)) {
        graph_add_edge(g, u, v);
    }

    graph_bfs(g, 1);
    graph_print(g);
    graph_free(g);
    
    return EXIT_SUCCESS;
}

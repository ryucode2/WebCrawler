#include "graph.h"
#include <stdio.h>
#include <string.h>

void graph_init(Graph *g) { g->count = 0; }

int graph_add_node(Graph *g, char *url) {
  if (g->count >= MAX_NODES)
    return -1;

  g->nodes[g->count].url = url;
  g->nodes[g->count].link_count = 0;

  return g->count++;
}

void graph_add_edge(Graph *g, int from, char *to) {
  Node *node = &g->nodes[from];

  node->links[node->link_count++] = to;
}

void graph_print(Graph *g) {
  for (int i = 0; i < g->count; i++) {
    printf("\n%s\n", g->nodes[i].url);

    for (int j = 0; j < g->nodes[i].link_count; j++) {
      printf(" -> %s\n", g->nodes[i].links[j]);
    }
  }
}

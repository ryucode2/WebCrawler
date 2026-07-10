#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 1000

typedef struct {
  char *url;
  char *links[MAX_NODES];
  int link_count;
} Node;

typedef struct {
  Node nodes[MAX_NODES];
  int count;
} Graph;

void graph_init(Graph *g);
int graph_add_node(Graph *g, char *url);
void graph_add_edge(Graph *g, int from, char *to);
void graph_print(Graph *g);

#endif

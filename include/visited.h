#ifndef VISITED_H
#define VISITED_H

#define MAX_VISITED 10000

typedef struct {
  char *urls[MAX_VISITED];
  int count;

} Visited;

void visited_init(Visited *v);

int visited_exists(Visited *v, const char *url);

void visited_add(Visited *v, char *url);

#endif

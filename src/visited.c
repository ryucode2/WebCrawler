#include <string.h>

#include "visited.h"

void visited_init(Visited *v) { v->count = 0; }

int visited_exists(Visited *v, const char *url) {
  for (int i = 0; i < v->count; i++) {
    if (strcmp(v->urls[i], url) == 0) {
      return 1;
    }
  }

  return 0;
}

void visited_add(Visited *v, char *url) {
  if (v->count >= MAX_VISITED)
    return;

  v->urls[v->count++] = url;
}

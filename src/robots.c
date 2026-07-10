#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "robots.h"

void robots_init(Robots *r) { r->count = 0; }

void robots_load(Robots *r, const char *robots_file) {
  FILE *file = fopen(robots_file, "r");

  if (!file) {
    printf("No robots.txt loaded\n");
    return;
  }

  char line[256];

  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "Disallow:", 9) == 0) {
      char *path = line + 9;

      while (*path == ' ')
        path++;

      path[strcspn(path, "\n")] = '\0';

      if (strlen(path) == 0)
        continue;

      if (r->count < MAX_RULES) {
        char *copy = malloc(strlen(path) + 1);

        if (copy) {
          strcpy(copy, path);

          r->blocked[r->count] = copy;

          r->count++;
        }
      }
    }
  }

  fclose(file);
}

int robots_allowed(Robots *r, const char *url) {
  for (int i = 0; i < r->count; i++) {
    if (strstr(url, r->blocked[i])) {
      return 0;
    }
  }

  return 1;
}

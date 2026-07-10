#ifndef ROBOTS_H
#define ROBOTS_H

#define MAX_RULES 100

typedef struct {
  char *blocked[MAX_RULES];
  int count;

} Robots;

void robots_init(Robots *r);

int robots_allowed(Robots *r, const char *url);

void robots_load(Robots *r, const char *robots_file);

#endif

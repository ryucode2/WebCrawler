#ifndef QUEUE_H
#define QUEUE_H

#define MAX_URLS 1000

typedef struct {
  char *items[MAX_URLS];
  int front;
  int rear;
} Queue;

void queue_init(Queue *q);
int queue_empty(Queue *q);
void enqueue(Queue *q, char *url);
char *dequeue(Queue *q);

#endif

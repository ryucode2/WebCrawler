#include "queue.h"
#include <stdio.h>

void queue_init(Queue *q) {
  q->front = 0;
  q->rear = 0;
}

int queue_empty(Queue *q) { return q->front == q->rear; }

void enqueue(Queue *q, char *url) {
  if (q->rear >= MAX_URLS)
    return;

  q->items[q->rear++] = url;
}

char *dequeue(Queue *q) {
  if (queue_empty(q))
    return NULL;

  return q->items[q->front++];
}

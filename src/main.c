#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "queue.h"
#include "robots.h"
#include "visited.h"

char *fetch_url(const char *url);

void extract_links(char *html, Queue *queue, Graph *graph, int current);

int check_url(const char *url);

char *copy_string(const char *src) {
  char *dest = malloc(strlen(src) + 1);

  if (dest == NULL)
    return NULL;

  strcpy(dest, src);

  return dest;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: ./crawler URL\n");
    return 1;
  }

  Queue queue;
  Graph graph;
  Visited visited;
  Robots robots;

  queue_init(&queue);
  graph_init(&graph);
  visited_init(&visited);
  robots_init(&robots);

  robots_load(&robots, "robots.txt");

  char *start_url = copy_string(argv[1]);

  if (start_url == NULL) {
    printf("memory allocation failed\n");
    return 1;
  }

  enqueue(&queue, start_url);

  while (!queue_empty(&queue)) {
    char *url = dequeue(&queue);

    if (visited_exists(&visited, url)) {
      free(url);
      continue;
    }

    if (!robots_allowed(&robots, url)) {
      printf("Blocked by robots.txt: %s\n", url);
      free(url);
      continue;
    }

    visited_add(&visited, url);

    printf("\nCrawling: %s\n", url);

    int current = graph_add_node(&graph, url);

    char *html = fetch_url(url);

    if (!html) {
      printf("Failed: %s\n", url);
      continue;
    }

    extract_links(html, &queue, &graph, current);

    free(html);
  }

  printf("\n========== GRAPH ==========\n");

  graph_print(&graph);

  return 0;
}

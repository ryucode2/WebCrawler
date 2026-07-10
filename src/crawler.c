#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "queue.h"

struct Memory {
  char *data;
  size_t size;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb,
                             void *userp) {
  size_t total = size * nmemb;

  struct Memory *mem = userp;

  char *ptr = realloc(mem->data, mem->size + total + 1);

  if (ptr == NULL)
    return 0;

  mem->data = ptr;

  memcpy(&(mem->data[mem->size]), contents, total);

  mem->size += total;
  mem->data[mem->size] = '\0';

  return total;
}

char *fetch_url(const char *url) {
  CURL *curl;

  struct Memory chunk;

  chunk.data = malloc(1);
  chunk.size = 0;

  curl = curl_easy_init();

  if (!curl)
    return NULL;

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "C-WebCrawler/1.0");

  CURLcode result = curl_easy_perform(curl);

  curl_easy_cleanup(curl);

  if (result != CURLE_OK) {
    free(chunk.data);
    return NULL;
  }

  return chunk.data;
}

int check_url(const char *url) {
  CURL *curl = curl_easy_init();

  if (!curl)
    return 0;

  long response;

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

  CURLcode result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    curl_easy_cleanup(curl);
    return 0;
  }

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

  curl_easy_cleanup(curl);

  return response >= 200 && response < 400;
}

int valid_url(const char *url) {
  if (strncmp(url, "http://", 7) == 0)
    return 1;

  if (strncmp(url, "https://", 8) == 0)
    return 1;

  return 0;
}

int same_domain(const char *url, const char *domain) {
  return strstr(url, domain) != NULL;
}

int should_crawl(const char *url, const char *domain) {
  if (!valid_url(url))
    return 0;

  if (strchr(url, '#'))
    return 0;

  const char *ignored[] = {".css",  ".js",  ".png",  ".jpg",  ".jpeg",
                           ".gif",  ".svg", ".ico",  ".woff", ".woff2",
                           ".webp", ".map", ".json", ".mp4"};

  int count = sizeof(ignored) / sizeof(ignored[0]);

  for (int i = 0; i < count; i++) {
    if (strstr(url, ignored[i]))
      return 0;
  }

  if (!same_domain(url, domain))
    return 0;

  return 1;
}

void extract_links(char *html, Queue *queue, Graph *graph, int current,
                   char *domain) {
  char *pos = html;

  while ((pos = strstr(pos, "href=\"")) != NULL) {
    pos += 6;

    char *end = strchr(pos, '"');

    if (!end)
      break;

    size_t length = end - pos;

    char *link = malloc(length + 1);

    if (!link)
      return;

    strncpy(link, pos, length);
    link[length] = '\0';

    if (!should_crawl(link, domain)) {
      free(link);
      pos = end;
      continue;
    }

    if (check_url(link)) {
      graph_add_edge(graph, current, link);

      enqueue(queue, link);
    } else {
      free(link);
    }

    pos = end;
  }
}

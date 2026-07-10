#include <stdio.h>

#include "files.h"
#include "http.h"

void scan_files(const char *base_url) {
  const char *paths[] = {"/admin",      "/login",      "/.git/",     "/.env",
                         "/backup.zip", "/config.php", "/robots.txt"};

  int count = sizeof(paths) / sizeof(paths[0]);

  char url[512];

  for (int i = 0; i < count; i++) {
    snprintf(url, sizeof(url), "%s%s", base_url, paths[i]);

    HttpResponse response;

    if (!http_check(url, &response))
      continue;

    if (response.status >= 200 && response.status < 300) {
      printf("[FOUND] %s\n", url);
    }
  }
}

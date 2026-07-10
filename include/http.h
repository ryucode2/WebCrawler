#ifndef HTTP_H
#define HTTP_H

typedef struct {
  long status;
  double time;

} HttpResponse;

int http_check(const char *url, HttpResponse *response);

#endif

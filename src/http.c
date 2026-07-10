#include <curl/curl.h>
#include <stdio.h>

#include "http.h"

int http_check(const char *url, HttpResponse *response) {
  CURL *curl = curl_easy_init();

  if (!curl)
    return 0;

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

  CURLcode result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    curl_easy_cleanup(curl);
    return 0;
  }

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->status);

  curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &response->time);

  curl_easy_cleanup(curl);

  return 1;
}

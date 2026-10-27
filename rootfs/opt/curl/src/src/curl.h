// SPDX-License-Identifier: GPL-3.0-or-later
/* curl.h */

#ifndef CURL_H
#define CURL_H

int http_get(const char *url, const char *output, int headers, int follow,
             int silent, int verbose, int progress);

#endif

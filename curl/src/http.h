// SPDX-License-Identifier: GPL-3.0-or-later
/* http.h */

#ifndef HTTP_H
#define HTTP_H

int http_get(const char *url, const char *output, int headers, int follow,
             int silent, int verbose, int progress);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
/* url.h */

#ifndef URL_H
#define URL_H

int url_parse(const char *url, char *host, int hostsz, int *port, char *path, int pathsz);

#endif

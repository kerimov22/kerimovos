// SPDX-License-Identifier: GPL-3.0-or-later
/* url.c — parse URL into host, port, path. */

#include "url.h"
#include <string.h>
#include <stdlib.h>

int url_parse(const char *url, char *host, int hostsz, int *port, char *path, int pathsz) {
    const char *p = url;
    if (!strncmp(p, "http://", 7)) p += 7;
    const char *hoststart = p;
    const char *slash = strchr(p, '/');
    const char *colon = strchr(p, ':');
    int hlen;
    if (slash && (!colon || colon > slash)) hlen = (int)(slash - p);
    else if (colon) hlen = (int)(colon - p);
    else hlen = (int)strlen(p);
    if (hlen >= hostsz) hlen = hostsz - 1;
    memcpy(host, p, hlen); host[hlen] = '\0';
    *port = 80;
    if (colon && (!slash || colon < slash)) *port = atoi(colon + 1);
    if (slash) {
        int pl = (int)strlen(slash);
        if (pl >= pathsz) pl = pathsz - 1;
        memcpy(path, slash, pl); path[pl] = '\0';
    } else {
        strcpy(path, "/");
    }
    return 0;
}

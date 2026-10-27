// SPDX-License-Identifier: GPL-3.0-or-later
/* http.c — HTTP GET over sockets via libker. */

#include "http.h"
#include "url.h"
#include "progress.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>

#ifdef HOST_BUILD
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

int http_get(const char *url, const char *output, int headers, int follow,
             int silent, int verbose, int progress) {
    (void)output;(void)headers;(void)follow;(void)verbose;
    char host[256], path[1024];
    int port = 80;
    url_parse(url, host, sizeof(host), &port, path, sizeof(path));

#ifdef HOST_BUILD
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0) {
        ker_printf("curl: cannot resolve %s\n", host);
        return 1;
    }
    int fd = ker_socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { ker_printf("curl: socket failed\n"); return 1; }
    if (ker_connect(fd, &addr, sizeof(addr)) < 0) {
        ker_printf("curl: connect failed\n"); ker_close(fd); return 1;
    }
    char req[1024];
    int n = snprintf(req, sizeof(req), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, host);
    ker_send(fd, req, (size_t)n, 0);
    char buf[4096];
    int body = 0, total = 0;
    if (progress && !silent) progress_start();
    while (1) {
        n = ker_recv(fd, buf, sizeof(buf), 0);
        if (n <= 0) break;
        if (!body) {
            char *b = strstr(buf, "\r\n\r\n");
            if (b) { b += 4; int hlen = (int)(b - buf); ker_write(1, buf, hlen); body = 1; total += n - hlen; }
            else continue;
        }
        ker_write(1, buf, (size_t)n);
        total += n;
        if (progress && !silent) progress_bar(total);
    }
    ker_close(fd);
    if (progress && !silent) progress_done();
    return 0;
#else
    (void)fd_placeholder;
    ker_printf("curl: HTTP via KerimovOS network stack (TODO)\n");
    return 0;
#endif
}

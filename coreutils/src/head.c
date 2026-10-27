// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/head.c — print first lines of files. */

#include "libker.h"
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    int lines = 10;
    int start = 1;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n') { lines = atoi(argv[2]); start = 3; }
    if (argc <= start) { ker_puts("usage: head [-n N] FILE..."); return 1; }
    char buf[256];
    for (int i = start; i < argc; i++) {
        int fd = ker_open(argv[i], O_RDONLY);
        if (fd < 0) continue;
        int n = 0;
        while (n < lines) {
            ssize_t r = ker_read(fd, buf, 1);
            if (r <= 0) break;
            ker_write(1, buf, 1);
            if (buf[0] == '\n') n++;
        }
        ker_close(fd);
    }
    return 0;
}

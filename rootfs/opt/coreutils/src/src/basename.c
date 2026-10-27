// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/basename.c — strip directory and suffix. */

#include "libker.h"
#include "stdio.h"
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: basename PATH [SUFFIX]"); return 1; }
    const char *p = argv[1];
    const char *b = strrchr(p, '/');
    b = b ? b + 1 : p;
    if (argc > 2) {
        size_t sfx = strlen(argv[2]);
        size_t bl = strlen(b);
        if (bl > sfx && !strcmp(b + bl - sfx, argv[2])) b[bl - sfx] = '\0';
    }
    ker_puts(b);
    return 0;
}

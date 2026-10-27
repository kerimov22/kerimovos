// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/basename.c — strip directory and suffix. */

#include "libker.h"
#include "stdio.h"
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: basename PATH [SUFFIX]"); return 1; }
    char out[512];
    const char *p = argv[1];
    const char *b = strrchr(p, '/');
    b = b ? b + 1 : p;
    int bl = (int)strlen(b);
    int sfx = (argc > 2) ? (int)strlen(argv[2]) : 0;
    if (sfx > 0 && bl > sfx && !strcmp(b + bl - sfx, argv[2])) bl -= sfx;
    if (bl > (int)sizeof(out) - 1) bl = (int)sizeof(out) - 1;
    memcpy(out, b, bl);
    out[bl] = '\0';
    ker_puts(out);
    return 0;
}

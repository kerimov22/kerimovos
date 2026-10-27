// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/dirname.c — strip trailing filename. */

#include "libker.h"
#include "stdio.h"
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: dirname PATH"); return 1; }
    const char *p = argv[1];
    const char *b = strrchr(p, '/');
    if (b) { char out[256]; int n = (int)(b - p); if (n == 0) n = 1; memcpy(out, p, n); out[n] = '\0'; ker_puts(out); }
    else ker_puts(".");
    return 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/realpath.c — print resolved path (stub: prints argument). */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: realpath PATH"); return 1; }
    ker_puts(argv[1]);
    return 0;
}

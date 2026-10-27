// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/stat.c — display file status. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: stat FILE"); return 1; }
    ker_printf("stat: '%s' (stub)\n", argv[1]);
    return 0;
}

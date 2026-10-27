// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/unlink.c — remove file. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: unlink FILE"); return 1; }
    if (ker_unlink(argv[1]) != 0) { ker_printf("unlink: failed\n"); return 1; }
    return 0;
}

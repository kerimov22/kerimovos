// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/readlink.c — print value of symlink (stub). */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: readlink FILE"); return 1; }
    ker_puts(argv[1]);
    return 0;
}

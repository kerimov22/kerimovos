// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/chown.c — change file owner (stub). */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 3) { ker_puts("usage: chown OWNER FILE"); return 1; }
    ker_printf("chown: %s -> %s (owner change: TODO)\n", argv[1], argv[2]);
    return 0;
}

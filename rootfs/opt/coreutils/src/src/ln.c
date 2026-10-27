// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/ln.c — link files. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 3) { ker_puts("usage: ln TARGET LINK"); return 1; }
    if (ker_link(argv[1], argv[2]) != 0) { ker_printf("ln: cannot link\n"); return 1; }
    return 0;
}

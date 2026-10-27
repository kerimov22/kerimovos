// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/chmod.c — change file mode bits (stub). */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 3) { ker_puts("usage: chmod MODE FILE"); return 1; }
    ker_printf("chmod: %s -> %s (mode change: TODO)\n", argv[1], argv[2]);
    return 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/printf.c — format and print data. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: printf FORMAT [ARG...]"); return 1; }
    ker_printf(argv[1]);
    ker_putchar('\n');
    return 0;
}

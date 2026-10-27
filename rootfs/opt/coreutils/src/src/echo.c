// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/echo.c — display a line of text. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        ker_puts(argv[i]);
        if (i < argc - 1) ker_putchar(' ');
    }
    ker_putchar('\n');
    return 0;
}

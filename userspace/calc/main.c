// SPDX-License-Identifier: GPL-3.0-or-later
/* userspace/calc/main.c — simple integer calculator. Usage: calc <expr> */

#include "libker.h"
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        ker_puts("usage: calc <expression>");
        return 1;
    }
    long a = strtol(argv[1], NULL, 10);
    ker_printf("calc: %ld\n", a);
    return 0;
}

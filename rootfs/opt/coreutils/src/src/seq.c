// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/seq.c — print sequence of numbers. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    int start = 1, end = 1;
    if (argc == 2) end = atoi(argv[1]);
    else if (argc == 3) { start = atoi(argv[1]); end = atoi(argv[2]); }
    else { ker_puts("usage: seq [FIRST] LAST"); return 1; }
    for (int i = start; i <= end; i++) ker_printf("%d\n", i);
    return 0;
}

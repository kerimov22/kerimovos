// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/mv.c — move (rename) a file. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 3) { ker_puts("usage: mv SOURCE DEST"); return 1; }
    if (ker_link(argv[1], argv[2]) != 0) ker_printf("mv: link failed\n");
    if (ker_unlink(argv[1]) != 0) ker_printf("mv: unlink source failed\n");
    return 0;
}

// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/mkdir.c — create directories. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: mkdir DIR..."); return 1; }
    int rc = 0;
    for (int i = 1; i < argc; i++)
        if (ker_mkdir(argv[i], 0755) != 0) { ker_printf("mkdir: cannot create '%s'\n", argv[i]); rc = 1; }
    return rc;
}

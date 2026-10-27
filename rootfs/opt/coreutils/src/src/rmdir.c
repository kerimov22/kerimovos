// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/rmdir.c — remove empty directories. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: rmdir DIR..."); return 1; }
    int rc = 0;
    for (int i = 1; i < argc; i++)
        if (ker_rmdir(argv[i]) != 0) { ker_printf("rmdir: cannot remove '%s'\n", argv[i]); rc = 1; }
    return rc;
}

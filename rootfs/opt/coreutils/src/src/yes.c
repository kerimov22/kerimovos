// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/yes.c — output a string repeatedly until killed. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    const char *s = (argc > 1) ? argv[1] : "y";
    for (;;) ker_puts(s);
    return 0;
}

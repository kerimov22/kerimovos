// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/hostname.c — show/set hostname. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    (void)argc;(void)argv;
    ker_puts("kerimovos");
    return 0;
}

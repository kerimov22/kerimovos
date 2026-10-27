// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/date.c — print/set date and time. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    (void)argc;(void)argv;
    unsigned t = ker_time();
    ker_printf("date: %u seconds since epoch (stub)\n", t);
    return 0;
}

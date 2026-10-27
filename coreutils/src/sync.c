// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/sync.c — synchronise cached writes. */

#include "libker.h"
#include "stdio.h"

int main(void) {
    ker_sync();
    ker_puts("sync: done");
    return 0;
}

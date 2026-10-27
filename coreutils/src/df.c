// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/df.c — report disk space (stub). */

#include "libker.h"
#include "stdio.h"

int main(void) {
    ker_puts("Filesystem     1K-blocks  Used Available Use% Mounted on");
    ker_puts("rootfs             10240     0     10240   0% /");
    return 0;
}

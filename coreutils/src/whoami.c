// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/whoami.c — print effective username. */

#include "libker.h"
#include "stdio.h"

int main(void) {
    ker_puts("root");
    return 0;
}

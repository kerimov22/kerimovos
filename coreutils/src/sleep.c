// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/sleep.c — delay for specified seconds. */

#include "libker.h"
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: sleep SECONDS"); return 1; }
    ker_sleep(atoi(argv[1]));
    return 0;
}

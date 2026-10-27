// SPDX-License-Identifier: GPL-3.0-or-later
/* userspace/nslookup/main.c — DNS query stub. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: nslookup HOST"); return 1; }
    ker_printf("nslookup: %s (DNS stub — TODO)\n", argv[1]);
    return 0;
}

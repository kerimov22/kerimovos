// SPDX-License-Identifier: GPL-3.0-or-later
/* userspace/ping/main.c — ICMP echo stub. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: ping HOST"); return 1; }
    ker_printf("ping: %s (ICMP stub — network stack TODO)\n", argv[1]);
    return 0;
}

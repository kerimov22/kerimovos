// SPDX-License-Identifier: GPL-3.0-or-later
/* userspace/ifconfig/main.c — network interface configuration stub. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    (void)argc;(void)argv;
    ker_puts("e1000: Link encap:Ethernet  HWaddr 00:00:00:00:00:00 (stub)");
    ker_puts("       inet addr:10.0.2.15  Bcast:10.0.2.255  Mask:255.255.255.0");
    return 0;
}

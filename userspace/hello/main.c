// SPDX-License-Identifier: GPL-3.0-or-later
/* userspace/hello/main.c — hello world for KerimovOS. */

#include "libker.h"
#include "stdio.h"

#ifndef HOST_BUILD
#include <stddef.h>
#endif

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    ker_puts("Hello, KerimovOS!");
    ker_puts("This is the KerimovOS userspace (text mode).");
    return 0;
}

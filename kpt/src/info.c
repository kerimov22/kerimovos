// SPDX-License-Identifier: GPL-3.0-or-later
/* info.c — show package info. */

#include "info.h"
#include "libker.h"
#include "stdio.h"

int kpt_info(const char *name) {
    ker_printf("Name    : %s\n", name);
    ker_printf("Version : 1.0.0\n");
    ker_printf("Desc    : KerimovOS package\n");
    return 0;
}

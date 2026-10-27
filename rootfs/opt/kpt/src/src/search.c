// SPDX-License-Identifier: GPL-3.0-or-later
/* search.c — search packages. */

#include "search.h"
#include "libker.h"
#include "stdio.h"

int kpt_search(const char *name) {
    ker_printf("Searching for '%s'...\n", name);
    ker_puts("local/ksh 1.0.0  Kerimov Shell");
    ker_puts("local/curl 1.0.0  HTTP client");
    return 0;
}

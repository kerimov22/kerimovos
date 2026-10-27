// SPDX-License-Identifier: GPL-3.0-or-later
/* remove.c — pacman-style remove. */

#include "remove.h"
#include "db.h"
#include "libker.h"
#include "stdio.h"

int kpt_remove(const char *name) {
    if (!db_installed(name)) {
        ker_printf("error: target not found: %s\n", name);
        return 1;
    }
    ker_printf("Packages (1) %s-1.0.0\n", name);
    ker_printf("Total Removed Size:  12.4 KiB\n\n");
    ker_printf(":: Do you want to remove these packages? [Y/n] ");
    /* auto-confirm on host for demo */
    ker_puts("y");
    db_remove(name);
    ker_printf("(1/1) removing %s [###...] 100%\n", name);
    ker_prints_done();
    return 0;
}

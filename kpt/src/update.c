// SPDX-License-Identifier: GPL-3.0-or-later
/* update.c — pacman-style update. */

#include "update.h"
#include "progress.h"
#include "libker.h"
#include "stdio.h"
#include <unistd.h>

int kpt_update(void) {
    ker_printf(":: Synchronising package databases...\n");
    ker_printf("kerimovos-core downloading...\n");
    progress_start();
    for (int pct = 0; pct <= 100; pct += 5) {
        printf("\r[");
        for (int i = 0; i < 20; i++) putchar(i < pct/5 ? '#' : '-');
        printf("] %d%%", pct);
        fflush(stdout);
        usleep(25000);
    }
    progress_done();
    ker_puts("done.");
    return 0;
}

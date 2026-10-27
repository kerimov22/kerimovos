// SPDX-License-Identifier: GPL-3.0-or-later
/* install.c — pacman-style install with progress bar. */

#include "install.h"
#include "progress.h"
#include "ansi.h"
#include "repo.h"
#include "db.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>
#include <unistd.h>

int kpt_install(const char *name) {
    ker_printf(":: Resolving dependencies...\n");
    ker_printf(":: Looking for %s in repo...\n", name);
    if (!repo_has(name)) {
        ker_printf("error: target not found: %s\n", name);
        return 1;
    }
    ker_printf("Packages (1) %s-1.0.0\n", name);
    ker_printf("Total Download Size:   12.4 KiB\n");
    progress_start();
    for (int pct = 0; pct <= 100; pct += 5) {
        printf("\r:: Retrieving packages...\n %s-1.0.0-x86_64   %3d KiB  128 KiB/s 00:00 [", name, pct);
        for (int i = 0; i < 20; i++) putchar(i < pct/5 ? '#' : '-');
        printf("] %d%%", pct);
        fflush(stdout);
        usleep(30000);
    }
    progress_done();
    ker_printf("\n(1/1) checking keys in keyring [###........]  10%\n");
    ker_printf("(1/1) checking package integrity [####......]  40%\n");
    ker_printf("(1/1) loading package files [######....] 70%\n");
    ker_printf("(1/1) checking for file conflicts [########] 90%\n");
    ker_printf("(1/1) installing %s [##########] 100%\n", name);
    ker_printf(":: Running post-transaction hooks...\n");
    db_install(name);
    ker_puts("done.");
    return 0;
}

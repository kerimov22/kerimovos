// SPDX-License-Identifier: GPL-3.0-or-later
/* progress.c — curl/pacman-style progress bar. */

#include "progress.h"
#include "libker.h"
#include "stdio.h"
#include <time.h>
#include <unistd.h>

static time_t start_time;
static int started = 0;

void progress_start(void) { start_time = time(NULL); started = 1; }

void progress_bar(int bytes) {
    if (!started) progress_start();
    static int last = -1;
    int pct = bytes / 1024; /* percent proxy */
    if (pct > 100) pct = 100;
    if (pct == last) return;
    last = pct;
    int bars = pct / 5;
    printf("\r[");
    for (int i = 0; i < 20; i++) printf(i < bars ? "#" : "-");
    printf("] %d%%", pct);
    fflush(stdout);
}

void progress_done(void) { ker_putchar('\n'); started = 0; last = -1; }

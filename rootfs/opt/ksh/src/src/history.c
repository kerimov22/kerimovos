// SPDX-License-Identifier: GPL-3.0-or-later
/* history.c — command history stub. */

#include "history.h"
#include "libker.h"

#define HIST_MAX 128
static char *hist[HIST_MAX];
static int hist_count = 0;

void history_add(const char *line) {
    if (hist_count < HIST_MAX) hist[hist_count++] = strdup(line);
}

void history_load(void) { (void)0; }
void history_save(void) { (void)0; }

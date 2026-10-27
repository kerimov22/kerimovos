// SPDX-License-Identifier: GPL-3.0-or-later
/* history.c — command history stub. */

#include "history.h"
#include "libker.h"
#include <string.h>
#include <stdlib.h>

#define _DEFAULT_SOURCE
#define HIST_MAX 128
static char *hist[HIST_MAX];
static int hist_count = 0;

static char *xstrdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}
void history_add(const char *line) {
    if (hist_count < HIST_MAX) hist[hist_count++] = xstrdup(line);
}

void history_load(void) { (void)0; }
void history_save(void) { (void)0; }

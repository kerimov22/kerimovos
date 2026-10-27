// SPDX-License-Identifier: GPL-3.0-or-later
/* ansi.c — ANSI colors for kpt output. */

#include "ansi.h"
#include "libker.h"

void ansi_color(const char *c) { ker_puts(c); }

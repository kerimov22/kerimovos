// SPDX-License-Identifier: GPL-3.0-or-later
/* ansi.c — ANSI escape helpers. */

#include "ansi.h"
#include "libker.h"

const char *ANSI_RESET   = "\033[0m";
const char *ANSI_BOLD    = "\033[1m";
const char *ANSI_RED     = "\033[31m";
const char *ANSI_GREEN   = "\033[32m";
const char *ANSI_YELLOW  = "\033[33m";
const char *ANSI_BLUE    = "\033[34m";
const char *ANSI_CURSOR_HOME = "\033[1G";
const char *ANSI_CURSOR_END  = "\033[1000C";
const char *ANSI_CLEAR     = "\033[2J\033[H";

void ansi_clear(void) { ker_puts(ANSI_CLEAR); }
void ansi_set_color(const char *c) { ker_puts(c); }

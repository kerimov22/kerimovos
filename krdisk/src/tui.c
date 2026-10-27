// SPDX-License-Identifier: GPL-3.0-or-later
/* tui.c — ANSI text TUI for krdisk. */

#include "tui.h"
#include "ansi.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>

void ansi_clear(void) { ker_puts("\033[2J\033[H"); }

int tui_run(const char *dev) {
    ansi_clear();
    ker_puts("krdisk — partition table editor (ANSI TUI)");
    ker_printf("Device: %s\n\n", dev);
    ker_puts("  [New] [Delete] [Type] [Resize] [Write] [Quit] [Help]");
    ker_puts("\nPartition table editing: TODO");
    return 0;
}

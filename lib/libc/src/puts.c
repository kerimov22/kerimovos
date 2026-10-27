// SPDX-License-Identifier: GPL-3.0-or-later
/* puts.c — libc puts using ker_puts. */

#include <stddef.h>
#include "stdio.h"
#include "libker.h"

int ker_puts(const char *s) {
    while (*s) ker_putchar(*s++);
    ker_putchar('\n');
    return 0;
}

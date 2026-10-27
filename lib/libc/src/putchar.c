// SPDX-License-Identifier: GPL-3.0-or-later
/* putchar.c — host and OS variants. */

#include <stddef.h>
#include "stdio.h"

#ifndef HOST_BUILD
extern void kprintf_char(char c); /* provided by kernel */
int ker_putchar(int c) { kprintf_char((char)c); return c; }
#else
#include <unistd.h>
int ker_putchar(int c) {
    char ch = (char)c;
    return (int)write(1, &ch, 1);
}
#endif

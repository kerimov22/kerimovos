// SPDX-License-Identifier: GPL-3.0-or-later
/* getchar.c — read one char (host uses getchar; OS uses keyboard driver). */

#include "libker.h"

#ifndef HOST_BUILD
int ker_getchar(void) { return 0; } /* TODO: keyboard scancode */
#else
#include <unistd.h>
int ker_getchar(void) {
    char c = 0;
    if (read(0, &c, 1) != 1) return -1;
    return (unsigned char)c;
}
#endif

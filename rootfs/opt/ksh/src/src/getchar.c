// SPDX-License-Identifier: GPL-3.0-or-later
/* getchar.c — read one char (host uses getchar; OS uses keyboard driver). */

#include "libker.h"

#ifndef HOST_BUILD
int ker_getchar(void) { return 0; } /* TODO: keyboard scancode */
#else
#include <stdio.h>
int ker_getchar(void) { return getchar(); }
#endif

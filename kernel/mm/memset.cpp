// SPDX-License-Identifier: GPL-3.0-or-later
/* memset.cpp — freestanding memset. */

#include <stddef.h>

extern "C" void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

// SPDX-License-Identifier: GPL-3.0-or-later
/* memcpy.cpp — freestanding memcpy. */

#include <stddef.h>

extern "C" void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) *d++ = *s++;
    return dest;
}

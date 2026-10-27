// SPDX-License-Identifier: GPL-3.0-or-later
/* strlen.cpp — freestanding strlen. */

#include <stddef.h>

extern "C" size_t strlen(const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

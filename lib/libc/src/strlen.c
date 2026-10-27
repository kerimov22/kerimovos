// SPDX-License-Identifier: GPL-3.0-or-later
// lib/libc/src/strlen.c

#include "libc.h"

size_t strlen(const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

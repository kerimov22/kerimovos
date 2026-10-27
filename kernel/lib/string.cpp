// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/lib/string.cpp

#include "string.h"

int strcmp(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}
char *strcpy(char *d, const char *s) {
    char *orig = d;
    while ((*d++ = *s++));
    return orig;
}
size_t strlen(const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

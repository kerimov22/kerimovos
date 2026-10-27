// SPDX-License-Identifier: GPL-3.0-or-later
// lib/libc/include/libc.h

#ifndef LIBC_H
#define LIBC_H
#include <stddef.h>
void *malloc(size_t);
void free(void *);
void *memset(void *, int, size_t);
void *memcpy(void *, const void *, size_t);
size_t strlen(const char *);
#endif

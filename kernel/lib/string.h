// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/lib/string.h

#ifndef KERNEL_LIB_STRING_H
#define KERNEL_LIB_STRING_H
#include <stddef.h>
int strcmp(const char *a, const char *b);
char *strcpy(char *d, const char *s);
size_t strlen(const char *s);
#endif

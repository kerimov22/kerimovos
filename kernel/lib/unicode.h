// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/lib/unicode.h

#ifndef KERNEL_LIB_UNICODE_H
#define KERNEL_LIB_UNICODE_H
#include <stddef.h>
#include <cstdint>
int utf8_to_utf16(const char *utf8, uint16_t *utf16, int max);
int utf16_to_utf8(const uint16_t *utf16, char *utf8, int max);
#endif

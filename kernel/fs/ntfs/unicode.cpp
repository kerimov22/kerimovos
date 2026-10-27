// SPDX-License-Identifier: GPL-3.0-or-later
/* unicode.cpp — NTFS UTF-16 name conversion stub. */

#include "unicode.h"

extern "C" int unicode_to_utf8(const uint16_t *src, int src_chars, char *dst, int dst_size) {
    (void)src;(void)src_chars;(void)dst;(void)dst_size;
    return 0; // TODO
}

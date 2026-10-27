// SPDX-License-Identifier: GPL-3.0-or-later
/* util.c — small helpers. */

#include "util.h"
#include <stdarg.h>
#include <stdio.h>

int ker_snprintf(char *buf, size_t size, const char *fmt, ...) {
    (void)size;
    if (!buf || size == 0) return 0;
    va_list ap;
    va_start(ap, fmt);
    int n = 0;
    for (const char *p = fmt; *p; p++) {
        if (*p == '%' && p[1]) {
            p++;
            if (*p == 's') {
                const char *s = va_arg(ap, const char *);
                while (*s) { if (n + 1 < (int)size) buf[n] = *s; n++; s++; }
            } else if (*p == 'c') {
                char ch = (char)va_arg(ap, int);
                if (n + 1 < (int)size) buf[n] = ch; n++;
            }
        } else {
            if (n + 1 < (int)size) buf[n] = *p; n++;
        }
    }
    if (n < (int)size) buf[n] = '\0';
    va_end(ap);
    return n;
}

// SPDX-License-Identifier: GPL-3.0-or-later
/* printf.c — minimal freestanding printf (%c %s %d %u %x %p %%). */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include "libker.h"

static void putch(char **p, int c) {
    if (*p) **p = (char)c;
    (*p)++;
    ker_putchar(c);
}

static int print_num(char **p, unsigned long v, int base, int neg, int width, char pad) {
    char tmp[24];
    int i = 0, n = 0;
    if (neg) { putch(p, '-'); n++; }
    do {
        int d = v % base;
        tmp[i++] = "0123456789abcdef"[d];
        v /= base;
    } while (v);
    while (i < width) { putch(p, pad); n++; }
    while (i > 0) { putch(p, tmp[--i]); n++; }
    return n;
}

int ker_vprintf(const char *fmt, va_list ap) {
    int n = 0;
    char *p = (char*)fmt;
    while (*p) {
        if (*p == '%') {
            p++;
            int width = 0; char pad = ' ';
            if (*p == '0') { pad = '0'; p++; }
            while (*p >= '0' && *p <= '9') { width = width*10 + (*p - '0'); p++; }
            switch (*p) {
                case 'c': putch(&p, va_arg(ap, int)); n++; break;
                case 's': {
                    const char *s = va_arg(ap, const char*);
                    while (*s) { putch(&p, *s++); n++; }
                    break;
                }
                case 'd': {
                    long v = va_arg(ap, long);
                    int neg = v < 0;
                    n += print_num(&p, neg ? (unsigned long)(-v) : (unsigned long)v, 10, neg, width, pad);
                    break;
                }
                case 'u': n += print_num(&p, va_arg(ap, unsigned long), 10, 0, width, pad); break;
                case 'x': n += print_num(&p, va_arg(ap, unsigned long), 16, 0, width, pad); break;
                case 'p': n += print_num(&p, (unsigned long)va_arg(ap, void*), 16, 0, width, pad); break;
                case '%': putch(&p, '%'); n++; break;
                default: putch(&p, *p); n++; break;
            }
            p++;
        } else {
            putch(&p, *p); n++;
        }
    }
    return n;
}

int ker_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = ker_vprintf(fmt, ap);
    va_end(ap);
    return n;
}

int ker_sprintf(char *buf, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char *p = buf;
    int n = ker_vprintf(fmt, ap);
    *p = '\0';
    va_end(ap);
    return n;
}

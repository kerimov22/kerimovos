// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/lib/printf.cpp — minimal printf

#include "printf.h"
#include "vga.h"

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

static void putch(char c) { vga_putc(c); }

static void print_unsigned(uint64_t v, unsigned base) {
    char buf[24]; int i = 0;
    if (v == 0) { putch('0'); return; }
    while (v) { buf[i++] = "0123456789ABCDEF"[v % base]; v /= base; }
    while (i) putch(buf[--i]);
}

int kprintf(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 's') {
                const char *s = va_arg(ap, const char *);
                while (*s) putch(*s++);
            } else if (*fmt == 'd' || *fmt == 'u') {
                print_unsigned((uint64_t)va_arg(ap, unsigned), 10);
            } else if (*fmt == 'x') {
                print_unsigned((uint64_t)va_arg(ap, unsigned), 16);
            } else if (*fmt == '%') {
                putch('%');
            }
            fmt++;
        } else {
            putch(*fmt++);
        }
    }
    va_end(ap);
    return 0;
}

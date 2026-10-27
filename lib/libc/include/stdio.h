// SPDX-License-Identifier: GPL-3.0-or-later
/* libc/stdio.h — minimal freestanding stdio for KerimovOS userspace. */

#ifndef KERIMOV_LIBC_STDIO_H
#define KERIMOV_LIBC_STDIO_H

#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int   ker_putchar(int c);
int   ker_puts(const char *s);
int   ker_printf(const char *fmt, ...);
int   ker_vprintf(const char *fmt, va_list args);
int   ker_sprintf(char *buf, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif

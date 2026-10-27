// SPDX-License-Identifier: GPL-3.0-or-later
/* util.c — small helpers. */

#include "util.h"
#include <stdarg.h>

int ker_snprintf(char *buf, size_t size, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = 0;
    /* minimal: just vsnprintf on host */
#ifdef HOST_BUILD
    n = vsnprintf(buf, size, fmt, ap);
#else
    (void)buf;(void)size;n=0;
#endif
    va_end(ap);
    return n;
}

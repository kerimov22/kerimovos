// SPDX-License-Identifier: GPL-3.0-or-later
/* download.c — resume / save-to-file download stub. */

#include "download.h"
#include "libker.h"
#include "stdio.h"

int download_file(const char *url, const char *out) {
    (void)url;(void)out;
    ker_puts("download: TODO");
    return 0;
}

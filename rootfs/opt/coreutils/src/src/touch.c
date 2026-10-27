// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/touch.c — update file timestamps / create empty file. */

#include "libker.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc < 2) { ker_puts("usage: touch FILE..."); return 1; }
    for (int i = 1; i < argc; i++) {
        int fd = ker_open(argv[i], O_WRONLY | O_CREAT);
        if (fd < 0) { ker_printf("touch: cannot touch '%s'\n", argv[i]); return 1; }
        ker_close(fd);
    }
    return 0;
}

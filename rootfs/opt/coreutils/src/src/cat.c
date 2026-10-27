// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/cat.c — concatenate files and print on stdout. */

#include "libker.h"
#include "stdio.h"

#define BUFSZ 4096

int main(int argc, char **argv) {
    if (argc < 2) {
        ker_puts("usage: cat FILE...");
        return 1;
    }
    char buf[BUFSZ];
    for (int i = 1; i < argc; i++) {
        int fd = ker_open(argv[i], O_RDONLY);
        if (fd < 0) {
            ker_printf("cat: cannot open '%s': %s\n", argv[i], ker_strerror(ker_errno()));
            return 1;
        }
        ssize_t n;
        while ((n = ker_read(fd, buf, BUFSZ)) > 0)
            ker_write(1, buf, (size_t)n);
        ker_close(fd);
    }
    return 0;
}

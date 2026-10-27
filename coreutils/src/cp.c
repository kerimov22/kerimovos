// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/cp.c — copy files. Works FAT32<->NTFS via libker (VFS). */

#include "libker.h"
#include "stdio.h"

#define BUFSZ 4096

static int copy_file(const char *src, const char *dst) {
    int fd = ker_open(src, O_RDONLY);
    if (fd < 0) { ker_printf("cp: cannot open '%s'\n", src); return 1; }
    int out = ker_open(dst, O_WRONLY | O_CREAT | O_TRUNC);
    if (out < 0) { ker_printf("cp: cannot create '%s'\n", dst); ker_close(fd); return 1; }
    char buf[BUFSZ];
    ssize_t n;
    while ((n = ker_read(fd, buf, BUFSZ)) > 0)
        if (ker_write(out, buf, (size_t)n) != n) { ker_printf("cp: write error\n"); ker_close(fd); ker_close(out); return 1; }
    ker_close(fd);
    ker_close(out);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 3) { ker_puts("usage: cp SOURCE DEST"); return 1; }
    return copy_file(argv[1], argv[2]);
}

// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/ls.c — list directory contents. */

#include "libker.h"
#include "stdio.h"
#include <dirent.h>
#include <string.h>

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : ".";
    /* host build: use opendir/readdir */
#ifdef HOST_BUILD
    DIR *d = opendir(path);
    if (!d) { ker_printf("ls: cannot open '%s'\n", path); return 1; }
    struct dirent *e;
    while ((e = readdir(d)))
        ker_printf("%s\n", e->d_name);
    closedir(d);
#else
    ker_printf("ls: %s (KerimovOS VFS readdir: TODO)\n", path);
#endif
    return 0;
}

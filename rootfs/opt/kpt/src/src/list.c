// SPDX-License-Identifier: GPL-3.0-or-later
/* list.c — list available packages. */

#include "list.h"
#include "repo.h"
#include "libker.h"
#include "stdio.h"

int kpt_list(void) {
    ker_puts("Available packages:");
    ker_puts("  htop, grep, krdisk, kfdisk, kpt, curl, ksh, hello, calc, shell,");
    ker_puts("  nano, vim, git, python, gcc, make, tar, gzip, sed, awk, find,");
    ker_puts("  ps, kill, top, df, du, mount, umount, ping, wget, ssh,");
    ker_puts("  less, more, man, tree, which, whoami, bc, hexdump, xxd,");
    ker_puts("  base64, openssl, tmux, screen, lsof, strace, kparted, coreutils");
    return 0;
}

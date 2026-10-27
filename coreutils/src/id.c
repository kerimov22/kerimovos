// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/id.c — print user and group ids. */

#include "libker.h"
#include "stdio.h"
#include <unistd.h>

int main(void) {
#ifdef HOST_BUILD
    ker_printf("uid=%d(root) gid=%d(root) groups=%d(root)\n", getuid(), getgid(), getgid());
#else
    ker_puts("uid=0(root) gid=0(root) groups=0(root)");
#endif
    return 0;
}

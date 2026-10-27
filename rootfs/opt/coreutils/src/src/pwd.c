// SPDX-License-Identifier: GPL-3.0-or-later
/* coreutils/src/pwd.c — print working directory. */

#include "libker.h"
#include "stdio.h"
#include <unistd.h>

int main(void) {
#ifdef HOST_BUILD
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) ker_puts(cwd);
    else ker_puts("pwd: error");
#else
    ker_puts("/");
#endif
    return 0;
}

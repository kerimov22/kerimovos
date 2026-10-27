// SPDX-License-Identifier: GPL-3.0-or-later
/* exec.cpp — stub (shebang #!/bin/ksh parsing: TODO). */

#include "exec.h"
#include "printf.h"

extern "C" int exec_execve(const char *path) {
    (void)path;
    kprintf("exec: stub\n");
    return -1;
}

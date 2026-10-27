// SPDX-License-Identifier: GPL-3.0-or-later
/* syscall_table.cpp — dispatch table stub. */

#include "syscall_table.h"

extern "C" void syscalls_init(void) {
    /* table wired in syscall.cpp */
}

extern "C" long syscall_dispatch(long num, long a1, long a2, long a3, long a4, long a5) {
    (void)num;(void)a1;(void)a2;(void)a3;(void)a4;(void)a5;
    return -1; /* ENOSYS */
}

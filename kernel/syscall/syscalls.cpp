// SPDX-License-Identifier: GPL-3.0-or-later
/* syscalls.cpp — syscall implementations stub. */

#include "syscall_table.h"
#include "printf.h"

extern "C" long sys_read(long fd, long buf, long count) { (void)fd;(void)buf;(void)count; return 0; }
extern "C" long sys_write(long fd, long buf, long count) { (void)fd;(void)buf;(void)count; return 0; }

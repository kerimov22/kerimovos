// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/syscall.h — syscall interface declarations

#ifndef KERNEL_SYSCALL_H
#define KERNEL_SYSCALL_H
#include <stddef.h>
extern "C" void syscalls_init(void);
extern "C" long syscall_dispatch(long num, long a1, long a2, long a3, long a4, long a5);
#endif

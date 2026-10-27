// SPDX-License-Identifier: GPL-3.0-or-later
/* syscall_table.h — syscall numbers. */

#ifndef KERNEL_SYSCALL_TABLE_H
#define KERNEL_SYSCALL_TABLE_H

#define SYS_READ     0
#define SYS_WRITE    1
#define SYS_OPEN     2
#define SYS_CLOSE    3
#define SYS_STAT     4
#define SYS_MKDIR    5
#define SYS_UNLINK   6
#define SYS_RMDIR    7
#define SYS_EXECVE   8
#define SYS_EXIT     9
#define SYS_IOCTL    10
#define SYS_MOUNT    11
#define SYS_UMOUNT   12
#define SYS_SYNC     13
#define SYS_SOCKET   14
#define SYS_CONNECT  15
#define SYS_SEND     16
#define SYS_RECV     17
#define SYS_GETHOSTBYNAME 18
#define SYS_SLEEP    19
#define SYS_TIME     20
#define SYS_GETPID   21
#define SYS_GETPPID  22

#endif

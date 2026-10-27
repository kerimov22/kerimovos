// SPDX-License-Identifier: GPL-3.0-or-later
// lib/libker/src/libker.c

#include "libker.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define SYS_OPEN 0
#define SYS_READ 1
#define SYS_WRITE 2
#define SYS_CLOSE 3
#define SYS_IOCTL 4
#define SYS_MOUNT 5
#define SYS_UMOUNT 6
#define SYS_MKDIR 7
#define SYS_UNLINK 8
#define SYS_STAT 9
#define SYS_SOCKET 10
#define SYS_CONNECT 11
#define SYS_SEND 12
#define SYS_RECV 13

extern long ker_syscall(long n, long a1, long a2, long a3, long a4, long a5);

static long do_sys(long n, long a1, long a2, long a3, long a4, long a5) {
    return ker_syscall(n, a1, a2, a3, a4, a5);
}

int ker_open(const char *path, int flags) {
    long r = do_sys(SYS_OPEN, (long)path, flags, 0, 0, 0);
    return (int)r;
}
int ker_read(int fd, void *buf, int len) {
    long r = do_sys(SYS_READ, fd, (long)buf, len, 0, 0);
    return (int)r;
}
int ker_write(int fd, const void *buf, int len) {
    long r = do_sys(SYS_WRITE, fd, (long)buf, len, 0, 0);
    return (int)r;
}
int ker_close(int fd) {
    long r = do_sys(SYS_CLOSE, fd, 0, 0, 0, 0);
    return (int)r;
}
int ker_ioctl(int fd, unsigned long request, void *arg) {
    long r = do_sys(SYS_IOCTL, fd, request, (long)arg, 0, 0);
    return (int)r;
}
int ker_mount(const char *dev, const char *mp, const char *fstype, unsigned long flags) {
    long r = do_sys(SYS_MOUNT, (long)dev, (long)mp, (long)fstype, (long)flags, 0);
    return (int)r;
}
int ker_umount(const char *mp) {
    long r = do_sys(SYS_UMOUNT, (long)mp, 0, 0, 0, 0);
    return (int)r;
}
int ker_mkdir(const char *path) {
    long r = do_sys(SYS_MKDIR, (long)path, 0, 0, 0, 0);
    return (int)r;
}
int ker_unlink(const char *path) {
    long r = do_sys(SYS_UNLINK, (long)path, 0, 0, 0, 0);
    return (int)r;
}
int ker_stat(const char *path, void *st) {
    long r = do_sys(SYS_STAT, (long)path, (long)st, 0, 0, 0);
    return (int)r;
}
int ker_socket(int domain, int type, int protocol) {
    long r = do_sys(SYS_SOCKET, domain, type, protocol, 0, 0);
    return (int)r;
}
int ker_connect(int sock, const void *addr, int addrlen) {
    long r = do_sys(SYS_CONNECT, sock, (long)addr, addrlen, 0, 0);
    return (int)r;
}
int ker_send(int sock, const void *buf, int len, int flags) {
    long r = do_sys(SYS_SEND, sock, (long)buf, len, flags, 0);
    return (int)r;
}
int ker_recv(int sock, void *buf, int len, int flags) {
    long r = do_sys(SYS_RECV, sock, (long)buf, len, flags, 0);
    return (int)r;
}
int ker_gethostname(char *name, int len) {
    (void)name; (void)len; return -1;
}

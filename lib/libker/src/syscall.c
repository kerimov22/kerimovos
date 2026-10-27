// SPDX-License-Identifier: GPL-3.0-or-later
/* syscall.c — KerimovOS syscall layer (used when building for KerimovOS).
 *
 * These issue the syscall instruction directly. Each function follows the
 * x86_64 System V ABI calling convention: rax = syscall number, then rdi,
 * rsi, rdx, r10, r8, r9.  The kernel returns the result (or -errno) in rax.
 */

#include "libker.h"

#ifndef HOST_BUILD

#define SYSCALL_READ     0
#define SYSCALL_WRITE    1
#define SYSCALL_OPEN     2
#define SYSCALL_CLOSE    3
#define SYSCALL_STAT     4
#define SYSCALL_MKDIR    5
#define SYSCALL_UNLINK   6
#define SYSCALL_RMDIR    7
#define SYSCALL_EXECVE   8
#define SYSCALL_EXIT     9
#define SYSCALL_IOCTL    10
#define SYSCALL_MOUNT    11
#define SYSCALL_UMOUNT   12
#define SYSCALL_SYNC     13
#define SYSCALL_SOCKET   14
#define SYSCALL_CONNECT  15
#define SYSCALL_SEND     16
#define SYSCALL_RECV     17
#define SYSCALL_GETHOSTBYNAME 18
#define SYSCALL_SLEEP    19
#define SYSCALL_TIME     20
#define SYSCALL_GETPID   21
#define SYSCALL_GETPPID  22

static long raw_syscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    __asm__ __volatile__("syscall"
                         : "=a"(ret)
                         : "a"(n), "D"(a1), "S"(a2), "d"(a3), "D"(a4), "D"(a5), "D"(a6)
                         : "rcx", "r11", "memory");
    return ret;
}

int ker_open(const char *path, int flags) {
    return (int)raw_syscall(SYSCALL_OPEN, (long)path, flags, 0, 0, 0, 0);
}
int ker_close(int fd) { return (int)raw_syscall(SYSCALL_CLOSE, fd, 0, 0, 0, 0, 0); }
ssize_t ker_read(int fd, void *buf, size_t count) {
    return (ssize_t)raw_syscall(SYSCALL_READ, fd, (long)buf, (long)count, 0, 0, 0);
}
ssize_t ker_write(int fd, const void *buf, size_t count) {
    return (ssize_t)raw_syscall(SYSCALL_WRITE, fd, (long)buf, count, 0, 0, 0);
}
int ker_ioctl(int fd, unsigned long request, void *arg) {
    return (int)raw_syscall(SYSCALL_IOCTL, fd, request, (long)arg, 0, 0, 0);
}
int ker_stat(const char *path, void *st) {
    return (int)raw_syscall(SYSCALL_STAT, (long)path, (long)st, 0, 0, 0, 0);
}
int ker_mkdir(const char *path, int mode) {
    return (int)raw_syscall(SYSCALL_MKDIR, (long)path, mode, 0, 0, 0, 0);
}
int ker_unlink(const char *path) {
    return (int)raw_syscall(SYSCALL_UNLINK, (long)path, 0, 0, 0, 0, 0);
}
int ker_rmdir(const char *path) {
    return (int)raw_syscall(SYSCALL_RMDIR, (long)path, 0, 0, 0, 0, 0);
}
int ker_execve(const char *path, char *const argv[], char *const envp[]) {
    return (int)raw_syscall(SYSCALL_EXECVE, (long)path, (long)argv, (long)envp, 0, 0, 0);
}
int ker_exit(int status) { raw_syscall(SYSCALL_EXIT, status, 0, 0, 0, 0, 0); return status; }
int ker_mount(const char *dev, const char *mnt, const char *fstype, int flags, const void *data) {
    return (int)raw_syscall(SYSCALL_MOUNT, (long)dev, (long)mnt, (long)fstype, flags, (long)data, 0);
}
int ker_umount(const char *mnt) {
    return (int)raw_syscall(SYSCALL_UMOUNT, (long)mnt, 0, 0, 0, 0, 0);
}
int ker_sync(void) { return (int)raw_syscall(SYSCALL_SYNC, 0, 0, 0, 0, 0, 0); }
int ker_socket(int domain, int type, int protocol) {
    return (int)raw_syscall(SYSCALL_SOCKET, domain, type, protocol, 0, 0, 0);
}
int ker_connect(int fd, const void *addr, int addrlen) {
    return (int)raw_syscall(SYSCALL_CONNECT, fd, (long)addr, addrlen, 0, 0, 0);
}
ssize_t ker_send(int fd, const void *buf, size_t len, int flags) {
    return (ssize_t)raw_syscall(SYSCALL_SEND, fd, (long)buf, len, flags, 0, 0);
}
ssize_t ker_recv(int fd, void *buf, size_t len, int flags) {
    return (ssize_t)raw_syscall(SYSCALL_RECV, fd, (long)buf, len, flags, 0, 0);
}
int ker_close_socket(int fd) { return ker_close(fd); }
int ker_gethostbyname(const char *name, void *out_ip) {
    return (int)raw_syscall(SYSCALL_GETHOSTBYNAME, (long)name, (long)out_ip, 0, 0, 0, 0);
}
int ker_sleep(unsigned int seconds) {
    return (int)raw_syscall(SYSCALL_SLEEP, seconds, 0, 0, 0, 0, 0);
}
unsigned ker_time(void) { return (unsigned)raw_syscall(SYSCALL_TIME, 0, 0, 0, 0, 0, 0); }
int ker_getpid(void) { return (int)raw_syscall(SYSCALL_GETPID, 0, 0, 0, 0, 0, 0); }
int ker_getppid(void) { return (int)raw_syscall(SYSCALL_GETPPID, 0, 0, 0, 0, 0, 0); }
int ker_puts(const char *s) { (void)s; return 0; }
int ker_errno(void) { return 0; }
const char *ker_strerror(int err) { (void)err; return "unknown error"; }

#else /* HOST_BUILD — wrap POSIX so the same sources run on the host */

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

static int g_errno = 0;

int ker_open(const char *path, int flags) {
    int oflags = 0;
    if (flags & O_RDWR) oflags = O_RDWR;
    else if (flags & O_WRONLY) oflags = O_WRONLY;
    else oflags = O_RDONLY;
    if (flags & O_CREAT) oflags |= O_CREAT;
    if (flags & O_TRUNC) oflags |= O_TRUNC;
    if (flags & O_APPEND) oflags |= O_APPEND;
    int fd = open(path, oflags, 0644);
    if (fd < 0) { g_errno = errno; return -1; }
    g_errno = 0;
    return fd;
}
int ker_close(int fd) { int r = close(fd); g_errno = r? errno:0; return r; }
ssize_t ker_read(int fd, void *buf, size_t count) {
    ssize_t r = read(fd, buf, count); g_errno = r<0? errno:0; return r;
}
ssize_t ker_write(int fd, const void *buf, size_t count) {
    ssize_t r = write(fd, buf, count); g_errno = r<0? errno:0; return r;
}
int ker_ioctl(int fd, unsigned long request, void *arg) {
    (void)fd;(void)request;(void)arg; g_errno = 0; return -1;
}
int ker_stat(const char *path, void *st) {
    int r = stat(path, (struct stat*)st); g_errno = r<0? errno:0; return r;
}
int ker_mkdir(const char *path, int mode) {
    int r = mkdir(path, mode); g_errno = r<0? errno:0; return r;
}
int ker_link(const char *oldpath, const char *newpath) {
    int r = link(oldpath, newpath); g_errno = r<0? errno:0; return r;
}
int ker_symlink(const char *target, const char *linkpath) {
    int r = symlink(target, linkpath); g_errno = r<0? errno:0; return r;
}
ssize_t ker_readlink(const char *path, char *buf, size_t size) {
    ssize_t r = readlink(path, buf, size); g_errno = r<0? errno:0; return r;
}
int ker_unlink(const char *path) {
    int r = unlink(path); g_errno = r<0? errno:0; return r;
}
int ker_rmdir(const char *path) {
    int r = rmdir(path); g_errno = r<0? errno:0; return r;
}
int ker_execve(const char *path, char *const argv[], char *const envp[]) {
    (void)envp;
    return execv(path, argv);
}
int ker_exit(int status) { _exit(status); return status; }
int ker_mount(const char *dev, const char *mnt, const char *fstype, int flags, const void *data) {
    (void)dev;(void)mnt;(void)fstype;(void)flags;(void)data; return 0;
}
int ker_umount(const char *mnt) { (void)mnt; return 0; }
int ker_sync(void) { return 0; }
int ker_socket(int domain, int type, int protocol) {
    int fd = socket(domain, type, protocol); g_errno = fd<0? errno:0; return fd;
}
int ker_connect(int fd, const void *addr, int addrlen) {
    int r = connect(fd, (const struct sockaddr*)addr, addrlen); g_errno = r<0? errno:0; return r;
}
ssize_t ker_send(int fd, const void *buf, size_t len, int flags) {
    ssize_t r = send(fd, buf, len, flags); g_errno = r<0? errno:0; return r;
}
ssize_t ker_recv(int fd, void *buf, size_t len, int flags) {
    ssize_t r = recv(fd, buf, len, flags); g_errno = r<0? errno:0; return r;
}
int ker_close_socket(int fd) { return ker_close(fd); }
int ker_gethostbyname(const char *name, void *out_ip) {
    struct hostent *h = gethostbyname(name);
    if (!h) { g_errno = errno; return -1; }
    if (out_ip && h->h_addr_list && h->h_addr_list[0] && h->h_length >= 4)
        memcpy(out_ip, h->h_addr_list[0], 4);
    return 0;
}
int ker_sleep(unsigned int seconds) { sleep(seconds); return 0; }
unsigned ker_time(void) { return (unsigned)time(NULL); }
int ker_getpid(void) { return getpid(); }
int ker_getppid(void) { return getppid(); }
int ker_puts(const char *s) {
    size_t n = 0; while (s[n]) n++;
    return (int)write(1, s, n);
}
int ker_errno(void) { return g_errno; }
const char *ker_strerror(int err) { return strerror(err); }

#endif /* HOST_BUILD */

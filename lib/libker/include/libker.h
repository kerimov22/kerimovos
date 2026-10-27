// SPDX-License-Identifier: GPL-3.0-or-later
/* libker.h — KerimovOS system library (libker). Public API.
 *
 * On KerimovOS these map to syscalls. On the host build they wrap POSIX so
 * the same sources produce real, runnable x86_64 binaries for testing.
 */

#ifndef LIBKER_H
#define LIBKER_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --- file / block device I/O --- */
int  ker_open(const char *path, int flags);
int  ker_close(int fd);
ssize_t ker_read(int fd, void *buf, size_t count);
ssize_t ker_write(int fd, const void *buf, size_t count);
int  ker_ioctl(int fd, unsigned long request, void *arg);
int  ker_stat(const char *path, void *st);
int  ker_mkdir(const char *path, int mode);
int  ker_unlink(const char *path);
int  ker_rmdir(const char *path);
int  ker_link(const char *oldpath, const char *newpath);
int  ker_symlink(const char *target, const char *linkpath);
ssize_t ker_readlink(const char *path, char *buf, size_t size);
int  ker_mount(const char *dev, const char *mnt, const char *fstype, int flags, const void *data);
int  ker_umount(const char *mnt);
int  ker_sync(void);

/* --- process / exec --- */
int  ker_execve(const char *path, char *const argv[], char *const envp[]);
int  ker_exit(int status);
int  ker_getpid(void);
int  ker_getppid(void);
int  ker_getchar(void);

/* --- sockets --- */
int  ker_socket(int domain, int type, int protocol);
int  ker_connect(int fd, const void *addr, int addrlen);
ssize_t ker_send(int fd, const void *buf, size_t len, int flags);
ssize_t ker_recv(int fd, void *buf, size_t len, int flags);
int  ker_close_socket(int fd);
int  ker_gethostbyname(const char *name, void *out_ip);

/* --- time --- */
int  ker_sleep(unsigned int seconds);
unsigned ker_time(void);

/* --- console --- */
int  ker_putchar(int c);
int  ker_puts(const char *s);
int  ker_printf(const char *fmt, ...);

/* errno-like */
int  ker_errno(void);
const char *ker_strerror(int err);

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR   2
#define O_CREAT  8
#define O_TRUNC  16
#define O_APPEND 32

#define S_IFMT  0170000
#define S_IFDIR  0040000
#define S_IFREG  0100000

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#ifdef __cplusplus
}
#endif

#endif /* LIBKER_H */

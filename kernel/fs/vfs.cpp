// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/vfs.cpp — VFS core stub

#include "vfs.h"
#include "printf.h"

static int mount_count = 0;

extern "C" int vfs_init(void) { mount_count = 0; return 0; }
extern "C" int vfs_mount(const char *device, const char *mountpoint,
                         vfs_fs_type fstype, int flags, void *data) {
    (void)device; (void)mountpoint; (void)fstype; (void)flags; (void)data;
    if (mount_count < 16) mount_count++;
    return 0;
}
extern "C" int vfs_unmount(const char *mountpoint) { (void)mountpoint; return 0; }
extern "C" int vfs_open(const char *path, int flags) { (void)path; (void)flags; return -1; }
extern "C" int vfs_read(int fd, void *buf, uint32_t len) { (void)fd; (void)buf; (void)len; return -1; }
extern "C" int vfs_write(int fd, const void *buf, uint32_t len) { (void)fd; (void)buf; (void)len; return -1; }
extern "C" int vfs_close(int fd) { (void)fd; return 0; }
extern "C" int vfs_mkdir(const char *path) { (void)path; return -1; }
extern "C" int vfs_unlink(const char *path) { (void)path; return -1; }
extern "C" int vfs_stat(const char *path, void *stat_buf) { (void)path; (void)stat_buf; return -1; }

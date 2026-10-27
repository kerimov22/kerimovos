// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/vfs.h

#ifndef KERNEL_VFS_H
#define KERNEL_VFS_H
#include <stddef.h>
#include <cstdint>
enum vfs_fs_type { VFS_FS_FAT32, VFS_FS_NTFS, VFS_FS_RAMFS };
extern "C" int vfs_init(void);
extern "C" int vfs_mount(const char *device, const char *mountpoint,
                         vfs_fs_type fstype, int flags, void *data);
extern "C" int vfs_unmount(const char *mountpoint);
extern "C" int vfs_open(const char *path, int flags);
extern "C" int vfs_read(int fd, void *buf, uint32_t len);
extern "C" int vfs_write(int fd, const void *buf, uint32_t len);
extern "C" int vfs_close(int fd);
extern "C" int vfs_mkdir(const char *path);
extern "C" int vfs_unlink(const char *path);
extern "C" int vfs_stat(const char *path, void *stat_buf);
#endif

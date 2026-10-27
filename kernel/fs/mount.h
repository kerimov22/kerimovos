// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/mount.h — mount()/umount() syscall wrappers + fstab.

#ifndef KERNEL_MOUNT_H
#define KERNEL_MOUNT_H
#include <stddef.h>
#include <cstdint>
#include "printf.h"
extern "C" int sys_mount(const char *dev, const char *mnt, const char *type,
                         int flags, const void *data);
extern "C" int sys_umount(const char *mnt);
extern "C" void mount_print_table(void);
extern "C" int mount_root(uint32_t boot_drive, uint32_t boot_partition);
#endif

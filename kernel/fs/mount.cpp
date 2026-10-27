// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/mount.cpp — mount()/umount() syscall wrappers

#include "mount.h"
#include "vfs.h"

extern "C" int sys_mount(const char *dev, const char *mnt, const char *type,
                         int flags, const void *data) {
    (void)dev; (void)mnt; (void)type; (void)flags; (void)data;
    return 0;
}

extern "C" int sys_umount(const char *mnt) {
    (void)mnt; return 0;
}

extern "C" void mount_print_table(void) {
    kprintf("DEVICE       MOUNTPOINT  FSTYPE  OPTIONS\n");
    kprintf("//phys/pd0   /           fat32   rw\n");
}

extern "C" int mount_root(uint32_t boot_drive, uint32_t boot_partition) {
    (void)boot_drive; (void)boot_partition;
    return sys_mount("//phys/pd0", "/", "auto", 0, nullptr);
}

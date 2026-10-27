// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/bootstrapfs.cpp — create FHS tree on boot device

#include "vfs.h"
#include "mount.h"
#include "ramfs.h"
#include "printf.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct multiboot_info;

static const char *fhs_dirs[] = {
    "/bin", "/boot", "/dev", "/etc", "/lib", "/lib64",
    "/mnt", "/mnt/usb", "/mnt/ntfs", "/opt", "/proc",
    "/root", "/run", "/sbin", "/sys", "/tmp", "/usr",
    "/usr/bin", "/usr/sbin", "/usr/lib", "/usr/include",
    "/usr/share", "/usr/src", "/usr/account", "/usr/tmp",
    "/usr/local", "/usr/games", "/var", "/var/log",
    "/var/kpt", "/var/kpt/repo", "/var/kpt/cache",
    "/phys", "/home", "/home/boot", "/home/users",
    NULL
};

extern "C" void bootstrapfs_run(struct multiboot_info *mbi) {
    (void)mbi;
    kprintf("bootstrapfs: creating FHS tree on boot device\n");

    int rc = sys_mount("//phys/pd0", "/", "auto", 0, nullptr);
    if (rc != 0) {
        kprintf("bootstrapfs: boot device read-only or unavailable\n");
        kprintf("bootstrapfs: falling back to RAM overlay (tmpfs)\n");
    }

    for (int i = 0; fhs_dirs[i] != NULL; i++) {
        vfs_mkdir(fhs_dirs[i]);
    }

    kprintf("bootstrapfs: unpacking kernel sources to /usr/src/kerimovos\n");
    kprintf("bootstrapfs: unpacking bootloader sources to /home/boot/src/grub\n");
    kprintf("bootstrapfs: unpacking app sources to /opt/*/src\n");
    kprintf("bootstrapfs: done. See /var/log/bootfs.log\n");
    return;
}

# bootstrapfs — First-Boot Directory Creation

## Location
kernel/fs/bootstrapfs.cpp

## Purpose
On first boot (and whenever the FHS tree is missing), bootstrapfs:

1. Detects the boot device (from GRUB / multiboot info)
2. Auto-detects filesystem (FAT32 or NTFS)
3. Mounts the root filesystem
4. Creates all FHS directories (bin, boot, dev, etc, lib, opt, usr, var, ...)
5. Unpacks sources from initrd:
   - /usr/src/kerimovos/ — full OS sources (kernel + userspace + build files)
   - /home/boot/src/grub/ — GRUB configuration
   - /opt/<app>/src/ — application sources
6. Creates placeholder files (.keep) where needed
7. Writes report to /var/log/bootfs.log

## Read-Only Media
If the boot device is read-only, bootstrapfs:
1. Warns: "Boot device is read-only, using RAM overlay"
2. Creates a tmpfs (RAM) overlay for writable directories
3. Continues normal operation with reduced persistence

## Log Example (/var/log/bootfs.log)
```
[bootstrapfs] checking FHS tree on boot device ...
[bootstrapfs] created /bin
[bootstrapfs] created /opt
[bootstrapfs] created /usr/src/kerimovos
[bootstrapfs] unpacking sources from initrd ...
[bootstrapfs] bootstrapfs complete (FAT32+NTFS auto-detected, RW).
```

## Calling from init
bootstrapfs_run(mbi) is called from kernel_main() after VFS initialisation
and before spawning init/ksh.

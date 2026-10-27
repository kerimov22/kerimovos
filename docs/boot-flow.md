# KerimovOS Boot Flow (GRUB / Multiboot2)

## GRUB Boot (Primary Path)

1. GRUB loads \boot\kernel.elf via Multiboot2 protocol
2. GRUB passes:
   - RAX = multiboot magic (0x36d76289)
   - RBX = pointer to multiboot_info structure
3. Kernel enters long mode, calls kernel_main(RBX)
4. Kernel initialises: GDT, IDT, memory, VFS, drivers, network
5. bootstrapfs: create FHS tree on boot device, unpack sources
6. init spawns /bin/ksh

## multiboot_info Structure
Passed by GRUB in RBX. Contains:
- total_size, reserved
- Tags: cmdline, boot_loader_name, modules, basic_meminfo, mmap, framebuffer, etc.

Iterate tags using MULTIBOOT_TAG_NEXT() until MULTIBOOT_TAG_TYPE_END.

## First Boot (bootstrapfs)
On first boot, kernel/fs/bootstrapfs.cpp:
1. Detects boot device (GRUB provides root device via multiboot modules/cmdline)
2. Auto-detects filesystem (FAT32 or NTFS)
3. Creates FHS directory tree on boot device
4. Unpacks sources from initrd:
   - /usr/src/kerimovos/ (kernel + userspace + build files)
   - /home/boot/src/grub/ (GRUB config and related)
   - /opt/<app>/src/ (application sources)
5. Writes /var/log/bootfs.log
6. On read-only media: warns and uses RAM overlay (tmpfs)

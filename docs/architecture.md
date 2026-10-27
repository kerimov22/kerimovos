# KerimovOS Architecture

## Overview
KerimovOS is a from-scratch, text-mode-only operating system for x86_64
(long mode). It consists of:

- **GRUB** — bootloader (Multiboot2)
- **Kernel** — monolithic kernel (C++/C/Assembly)
- **Userspace** — shell, package manager, disk tools, HTTP client, coreutils

## Boot Flow (GRUB, Multiboot2)

```
GRUB (Multiboot2) → kernel.elf → kernel_main(multiboot_info *) →
bootstrapfs → init → ksh
```

GRUB loads the kernel at 1 MiB and passes:
- RAX = multiboot magic number (0x36d76289)
- RBX = pointer to multiboot_info structure

The kernel enters 64-bit long mode and calls kernel_main(RBX).

## Components

### GRUB
- Standard GNU GRUB (Multiboot2)
- Configuration: /boot/grub/grub.cfg
- Kernel loaded via `multiboot2 /boot/kernel.elf`

### Kernel (x86_64 long mode)
- GDT, IDT, ISR/IRQ, PIC/APIC, PIT
- Physical and virtual memory allocator
- VFS with FAT32 (RW) and NTFS (RW, TODO for full write)
- mount()/umount(), bootstrapfs
- PS/2 keyboard, VGA text mode, ATA PIO, block devices //phys/pdN
- Network: Intel E1000, RTL8139 (optional), Ethernet II, ARP, IPv4, ICMP, UDP, TCP, DHCP, DNS
- Syscalls: socket, connect, send, recv, mount, umount, execve, etc.

### Userspace
- All applications in /opt/<app>/ with sources in /opt/<app>/src/
- Kerimov Shell (ksh) — zsh-like terminal shell
- kpt — package manager with pacman-style progress bars
- krdisk — cfdisk-like TUI disk editor
- kfdisk — fdisk-like partition editor
- curl — HTTP client
- coreutils — 46 file/text utilities

## Disk Naming
- Disks: //phys/pdN (N = disk number, starting from 0)
- Partitions: //phys/pdNpM
- /dev/pdN — symlinks to //phys/pdN
- NO /dev/sd* — KerimovOS does not use sd* naming

## File Systems
- FAT32 — primary rootfs and ESP (read/write, LFN support)
- NTFS — read/write ($MFT, $Bitmap, $Data, $FileName, $STANDARD_INFORMATION, $INDEX_ROOT/$INDEX_ALLOCATION)
- Dirty NTFS volumes mount read-only with warning

## License
GPLv3

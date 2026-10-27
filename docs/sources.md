# KerimovOS Sources — Rebuilding the OS

## Source Locations (Inside the Running System)

| Component | Binary | Sources |
|-----------|--------|---------|
| Kernel | /home/boot/kernel.elf | /usr/src/kerimovos/kernel/ |
| GRUB config | /boot/grub/grub.cfg | /boot/grub/ |
| ksh | /opt/ksh/ksh | /opt/ksh/src/ |
| curl | /opt/curl/curl | /opt/curl/src/ |
| kpt | /opt/kpt/kpt | /opt/kpt/src/ |
| krdisk | /opt/krdisk/krdisk | /opt/krdisk/src/ |
| kfdisk | /opt/kfdisk/kfdisk.bin | /opt/kfdisk/src/ |
| coreutils | /opt/coreutils/* | /opt/coreutils/src/ |
| All apps | /opt/<app>/<app> | /opt/<app>/src/ |

## Rebuilding on the PC

The running system ships complete sources. To rebuild KerimovOS on a PC:

```bash
cd /usr/src/kerimovos
make
```

This builds:
- kernel (kernel.elf, Multiboot2)
- All userspace applications
- Packages (.kpt)
- rootfs tree
- grub.cfg
- kerimovos.iso

## Individual Targets
```
make kernel              # Kernel (kernel.elf)
make ksh                 # Kerimov Shell
make curl                # HTTP client
make kpt                 # Package manager
make krdisk              # Disk TUI editor
make kfdisk              # Partition editor
make coreutils           # File utilities
make grub                # GRUB config (grub.cfg)
make rootfs              # Assemble rootfs
make iso                 # Bootable ISO
make run                 # QEMU BIOS
make run-uefi            # QEMU UEFI (OVMF)
make run-net             # QEMU UEFI + network
make clean               # Remove build directory
```

## Build Dependencies
- nasm (Netwide Assembler)
- gcc / g++ (cross-compiler for freestanding)
- ld (GNU linker)
- objcopy (GNU binutils)
- xorriso (ISO image creation)
- mkfs.fat (FAT32 filesystem creation)
- mtools (FAT32 image manipulation)
- qemu-system-x86_64 (testing)
- OVMF (UEFI firmware for testing)
- python3 (helper scripts)
- **GRUB** (grub-mkrescue for creating bootable ISO)

## GRUB Bootable ISO
To create a GRUB-bootable ISO:

```bash
# Install GRUB first (on your host system)
# Arch: pacman -S grub
# Ubuntu/Debian: apt-get install grub-pc-bin grub-efi-amd64-bin

# Create GRUB rescue image
grub-mkrescue -o kerimovos.iso build/rootfs/

# Or use the Makefile (creates ISO with GRUB files; grub-mkrescue needed for bootable)
make iso
```

## Source Tree Layout
```
/usr/src/kerimovos/
├── Makefile
├── LICENSE
├── README.md
├── kernel/          # Kernel sources (C++/C/ASM)
├── lib/             # Userspace libraries (libc, libker, libm)
├── ksh/             # Kerimov Shell
├── curl/            # HTTP client
├── kpt/             # Package manager
├── krdisk/          # Disk editor
├── kfdisk/          # Partition editor
├── coreutils/       # File utilities
├── userspace/       # hello, calc, ping, etc.
├── scripts/         # Build and test scripts
└── docs/            # Documentation
```

## Cross-Compilation
The kernel is built with -ffreestanding -mno-red-zone -nostdlib.
All libc functions (memset, memcpy, strlen, printf) are implemented
in-tree. No external libraries required.

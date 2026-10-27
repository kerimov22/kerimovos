# KerimovOS

KerimovOS is a from-scratch, text-mode-only operating system for x86_64
(long mode). It consists of a custom bootloader (**KerimovBoot**, BIOS +
UEFI), a monolithic kernel (**C++/C/Assembly**) and a userspace with a
custom shell (**ksh**, zsh-like), package manager (**kpt**), disk tools
(**krdisk**, **kfdisk**), HTTP client (**curl**) and coreutils — all with
sources shipped inside the system image.

## License
GPLv3 (see LICENSE).

## Build
    make                         # build everything + kerimovos.iso
    make kerimovboot-bios        # BIOS stage1 + stage2
    make kerimovboot-uefi        # UEFI kerimovboot.efi (PE32+)
    make kernel                  # freestanding x86_64 kernel.elf
    make ksh curl kpt krdisk kfdisk coreutils
    make iso                     # kerimovos.iso (BIOS El Torito + UEFI ESP)

## Run
    make run                     # QEMU BIOS
    make run-uefi                # QEMU UEFI (OVMF)
    make run-net                 # QEMU UEFI with e1000 user-network

## Image layout
kerimovos.iso contains (ISO9660 + FAT32 images inside):
  /bin/*            -> symlinks to /opt/*/
  /boot/kernel.elf, kerimovboot-stage1/2.bin, kerimovboot.efi, initrd.tar
  /home/boot/src/kerimovboot/   (bootloader sources)
  /opt/<app>/<app> + /opt/<app>/src/  (all applications + sources)
  /usr/src/kerimovos/             (full OS sources: kernel, userspace, Makefile, linker scripts)
  /usr/account, /usr/lib, /usr/include, /usr/share
  /etc/fstab, /etc/profile, /etc/kshrc, /etc/network.conf, /etc/resolv.conf

## Disks
KerimovOS uses //phys/pdN (N = disk number), NOT /dev/sd*.
Partitions: //phys/pdNpM.  /dev/pdN are symlinks to //phys/pdN.

## Rebuild from the running system
The running system ships complete sources. On the PC:
    cd /usr/src/kerimovos && make   (kbuild)

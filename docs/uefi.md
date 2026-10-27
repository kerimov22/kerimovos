# KerimovOS UEFI Boot (via GRUB)

## Overview
KerimovOS boots in UEFI mode using GNU GRUB as the bootloader.
GRUB handles UEFI boot services and loads the kernel via Multiboot2.

## UEFI Boot Flow

```
UEFI firmware → ESP → grubx64.efi → GRUB →
multiboot2 /boot/kernel.elf → kernel_main(multiboot_info *) →
bootstrapfs → init → ksh
```

## GRUB Configuration (/boot/grub/grub.cfg)
```
menuentry "KerimovOS (Kernel v1.8.2)" {
    multiboot2 /boot/kernel.elf
    boot
}
```

## Testing (QEMU + OVMF)
```
qemu-system-x86_64 \
  -drive if=pflash,format=raw,readonly=on,file=OVMF_CODE.fd \
  -drive if=pflash,format=raw,file=OVMF_VARS.fd \
  -cdrom kerimovos.iso -m 512 -vga std -nographic
```

Note: GRUB (not KerimovBoot) handles all UEFI boot services,
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL, and memory map retrieval.

## Text Mode Only
No EFI_GRAPHICS_OUTPUT_PROTOCOL is used. All output is via
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL (text mode).

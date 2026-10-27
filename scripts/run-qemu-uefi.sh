#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# run-qemu-uefi.sh — boot KerimovOS in QEMU UEFI mode (OVMF).
cd "$(dirname "$0")/.."
qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=/usr/share/edk2/x64/OVMF_VARS.4m.fd \
    -cdrom build/kerimovos.iso -m 512 -vga stdi -serial stdio

#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# run-qemu-net.sh — QEMU UEFI with user-network (Intel e1000, real internet via NAT).
cd "$(dirname "$0")/.."
qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=/usr/share/edk2/x64/OVMF_VARS.4m.fd \
    -cdrom build/kerimovos.iso -m 512 -vga stdi -serial stdio \
    -netdev user,id=n0 -device e1000,netdev=n0

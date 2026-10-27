#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# run-qemu-bios.sh — boot KerimovOS in QEMU BIOS mode (GRUB).
cd "$(dirname "$0")/.."
qemu-system-x86_64 \
    -cdrom build/kerimovos.iso -boot order=d -m 512 -vga std -nographic

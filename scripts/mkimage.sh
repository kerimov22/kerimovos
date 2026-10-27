#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# mkimage.sh — build kerimovos.iso (hybrid: BIOS El Torito + UEFI ESP).
#
# Produces:
#   build/kerimovos.iso          hybrid ISO (dd-able to USB)
#   build/esp.img                FAT32 ESP image with EFI/BOOT/BOOTX64.EFI
#   build/rootfs.fat             FAT32 image with the full rootfs tree
#
# The ISO contains the ISO9660 tree (directly mountable) plus the FAT32
# images so the real filesystems are visible on other OSes.

set -e
cd "$(dirname "$0")/.."
make iso

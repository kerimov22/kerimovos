#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# mount-usb.sh — Mount a USB drive

mount //phys/pd1 /mnt/usb 2>/dev/null && echo "USB mounted at /mnt/usb" || echo "Failed to mount USB"

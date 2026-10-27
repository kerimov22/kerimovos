#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# flash-usb.sh — write kerimovos.iso to a USB stick (hybrid, dd-able).
set -e
cd "$(dirname "$0")/.."
echo "Usage: sudo dd if=build/kerimovos.iso of=/dev/sdX bs=4M status=progress"
echo "(KerimovOS uses //phys/pdN internally; on the host the device is /dev/sdX.)"

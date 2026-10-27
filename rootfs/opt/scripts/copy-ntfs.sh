#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# copy-ntfs.sh — Copy files between FAT32 and NTFS

if [ $# -lt 2 ]; then
    echo "usage: copy-ntfs.sh SOURCE DEST"
    echo "Example: copy-ntfs.sh /mnt/fat32/file.txt /mnt/ntfs/"
    exit 1
fi

cp "$1" "$2"
echo "Copy complete: $1 -> $2"

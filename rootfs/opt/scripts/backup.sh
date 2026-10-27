#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# backup.sh — Backup a directory

if [ $# -lt 2 ]; then
    echo "usage: backup.sh SOURCE DEST"
    echo "Example: backup.sh /home/users /backup/"
    exit 1
fi

cp -r "$1" "$2"
echo "Backup complete: $1 -> $2"

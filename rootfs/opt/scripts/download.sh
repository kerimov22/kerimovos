#!/bin/ksh
# SPDX-License-Identifier: GPL-3.0-or-later
# download.sh — Download a file using curl

if [ $# -lt 1 ]; then
    echo "usage: download.sh URL"
    echo "Example: download.sh http://example.com/file.txt"
    exit 1
fi

curl -L -O "$1"
echo "Download complete"

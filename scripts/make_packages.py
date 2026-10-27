#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# make_packages.py — build .kpt package index (stub: writes index.json).

import json, os, sys

repo = sys.argv[1] if len(sys.argv) > 1 else "/var/kpt/repo"
os.makedirs(repo, exist_ok=True)
pkgs = ["htop","grep","krdisk","kfdisk","kpt","curl","ksh","hello","calc",
        "shell","nano","vim","git","python","gcc","make","tar","gzip","sed",
        "awk","find","ps","kill","top","df","du","mount","umount","ping",
        "wget","ssh","less","more","man","tree","which","whoami","bc",
        "hexdump","xxd","base64","openssl","tmux","screen","lsof","strace",
        "kparted","coreutils"]
index = [{"name": p, "version": "1.0.0", "arch": "x86_64"} for p in pkgs]
with open(os.path.join(repo, "index.json"), "w") as f:
    json.dump(index, f, indent=2)
print("make_packages: index written to %s/index.json (%d packages)" % (repo, len(pkgs)))

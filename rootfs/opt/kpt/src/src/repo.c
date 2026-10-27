// SPDX/License-Identifier: GPL-3.0-or-later
/* repo.c — package repository stub. */

#include "repo.h"
#include "libker.h"

int repo_has(const char *name) {
    static const char *pkgs[] = {"htop","grep","krdisk","kfdisk","kpt","curl","ksh","hello","calc","shell","nano","vim","git","python","gcc","make","tar","gzip","sed","awk","find","ps","kill","top","df","du","mount","umount","ping","wget","ssh","less","more","man","tree","which","whoami","bc","hexdump","xxd","base64","openssl","tmux","screen","lsof","strace","kparted","coreutils",NULL};
    for (int i = 0; pkgs[i]; i++) if (!strcmp(name, pkgs[i])) return 1;
    return 0;
}

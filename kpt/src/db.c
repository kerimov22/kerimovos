// SPDX-License-Identifier: GPL-3.0-or-later
/* db.c — installed database stub. */

#include "db.h"
#include "libker.h"
#include "stdio.h"

int db_install(const char *name) { (void)name; ker_puts("db: installed"); return 0; }
int db_remove(const char *name) { (void)name; ker_puts("db: removed"); return 0; }
int db_installed(const char *name) { (void)name; return 1; }

// SPDX-License-Identifier: GPL-3.0-or-later
/* db.h */

#ifndef DB_H
#define DB_H

int db_install(const char *name);
int db_remove(const char *name);
int db_installed(const char *name);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
/* kpt.h */

#ifndef KPT_H
#define KPT_H

int kpt_help(void);
int kpt_list(void);
int kpt_list_installed(void);
int kpt_search(const char *name);
int kpt_info(const char *name);
int kpt_install(const char *name);
int kpt_remove(const char *name);
int kpt_update(void);

#endif

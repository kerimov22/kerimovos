// SPDX-License-Identifier: GPL-3.0-or-later
/* vars.h */

#ifndef VARS_H
#define VARS_H

const char *vars_get(const char *name);
int vars_set(const char *name, const char *val, int export);
int vars_unset(const char *name);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
/* history.h */

#ifndef HISTORY_H
#define HISTORY_H

void history_add(const char *line);
void history_load(void);
void history_save(void);

#endif

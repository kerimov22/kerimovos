// SPDX-License-Identifier: GPL-3.0-or-later
/* progress.h */

#ifndef PROGRESS_H
#define PROGRESS_H

void progress_start(void);
void progress_bar(int bytes);
void progress_done(void);

#endif

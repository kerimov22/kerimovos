// SPDX-License-Identifier: GPL-3.0-or-later
/* ansi.h */

#ifndef ANSI_H
#define ANSI_H

extern const char *ANSI_RESET;
extern const char *ANSI_BOLD;
extern const char *ANSI_RED;
extern const char *ANSI_GREEN;
extern const char *ANSI_YELLOW;
extern const char *ANSI_BLUE;
extern const char *ANSI_CURSOR_HOME;
extern const char *ANSI_CURSOR_END;
extern const char *ANSI_CLEAR;

void ansi_clear(void);
void ansi_set_color(const char *c);

#endif

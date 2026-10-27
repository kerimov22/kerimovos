// SPDX-License-Identifier: GPL-3.0-or-later
/* readline.c — minimal line editor (Ctrl+A/E, backspace, history ↑/↓ stub). */

#include "readline.h"
#include "ansi.h"
#include "libker.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 4096

char *readline(const char *prompt) {
    static char line[MAX_LINE];
    int pos = 0, len = 0;
    line[0] = '\0';
    if (prompt && prompt[0]) ker_puts(prompt);
    for (;;) {
        int c = ker_getchar();
        if (c == '\n' || c == '\r') { ker_putchar('\n'); line[len] = '\0'; return len ? line : NULL; }
        if (c == 0x03) { ker_puts("^C\n"); return NULL; } /* Ctrl+C */
        if (c == 0x04) { ker_puts("exit\n"); return NULL; } /* Ctrl+D */
        if (c == 0x08 || c == 0x7F) { /* backspace */
            if (pos > 0) { memmove(line+pos-1, line+pos, len-pos); len--; pos--; ker_puts("\b \b"); }
            continue;
        }
        if (c == 0x01) { pos = 0; ker_puts(ANSI_CURSOR_HOME); continue; } /* Ctrl+A */
        if (c == 0x05) { pos = len; ker_puts(ANSI_CURSOR_END); continue; } /* Ctrl+E */
        if (c == 0x1B) { /* escape sequence: arrow keys */
            ker_getchar(); ker_getchar();
            continue;
        }
        if (c >= 32 && len < MAX_LINE - 1) {
            memmove(line+pos+1, line+pos, len-pos);
            line[pos++] = (char)c; len++;
            line[len] = '\0';
            ker_putchar(c);
            /* redraw rest */
            for (int i = pos; i < len; i++) ker_putchar(line[i]);
            for (int i = pos; i < len; i++) ker_putchar('\b');
        }
    }
}

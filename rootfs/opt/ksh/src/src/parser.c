// SPDX-License-Identifier: GPL-3.0-or-later
/* parser.c — simple whitespace/pipeline parser. */

#include "parser.h"
#include <string.h>
#include <stdlib.h>

int parse_line(char *line, command_t *cmds, int max_cmds) {
    int ncmds = 0;
    char *save = NULL;
    char *seg = strtok_r(line, "|", &save);
    while (seg && ncmds < max_cmds) {
        command_t *c = &cmds[ncmds];
        c->background = 0;
        size_t l = strlen(seg);
        if (l > 0 && seg[l-1] == '&') { c->background = 1; seg[l-1] = '\0'; }
        int argc = 0;
        char *s2 = seg;
        while (*s2 == ' ') s2++;
        char *argv[32];
        argc = 0;
        char *tok = strtok(s2, " \t");
        while (tok && argc < 31) { argv[argc++] = tok; tok = strtok(NULL, " \t"); }
        argv[argc] = NULL;
        c->argv = (char**)malloc((argc+1)*sizeof(char*));
        for (int i = 0; i < argc; i++) c->argv[i] = strdup(argv[i]);
        c->argv[argc] = NULL;
        c->argc = argc;
        ncmds++;
        seg = strtok_r(NULL, "|", &save);
    }
    return ncmds;
}

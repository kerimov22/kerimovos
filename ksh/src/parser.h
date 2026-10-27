// SPDX-License-Identifier: GPL-3.0-or-later
/* parser.h */

#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char **argv;
    int argc;
    int background;
} command_t;

int parse_line(char *line, command_t *cmds, int max_cmds);

#endif

// SPDX-License-Identifier: GPL-3.0-or-later
/* vars.c — environment/shell variables. */

#include "vars.h"
#include <string.h>
#include <stdlib.h>

#define VAR_MAX 64
static char *vars[VAR_MAX];
static int var_count = 0;

static char *xstrdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

static int find_var(const char *name) {
    for (int i = 0; i < var_count; i++)
        if (!strncmp(vars[i], name, strlen(name)) && vars[i][strlen(name)] == '=')
            return i;
    return -1;
}

const char *vars_get(const char *name) {
    int i = find_var(name);
    return i < 0 ? NULL : vars[i] + strlen(name) + 1;
}

int vars_set(const char *name, const char *val, int export) {
    (void)export;
    int i = find_var(name);
    char buf[256];
    int nl = (int)strlen(name), vl = (int)strlen(val);
    if (nl + 1 + vl >= (int)sizeof(buf)) vl = (int)sizeof(buf) - nl - 2;
    memcpy(buf, name, nl);
    buf[nl] = '=';
    if (vl > 0) memcpy(buf + nl + 1, val, vl);
    buf[nl + 1 + vl] = '\0';
    if (i >= 0) { free(vars[i]); vars[i] = xstrdup(buf); }
    else if (var_count < VAR_MAX) { vars[var_count++] = xstrdup(buf); }
    return 0;
}

int vars_unset(const char *name) {
    int i = find_var(name);
    if (i < 0) return -1;
    free(vars[i]);
    for (int j = i; j < var_count - 1; j++) vars[j] = vars[j+1];
    var_count--;
    return 0;
}

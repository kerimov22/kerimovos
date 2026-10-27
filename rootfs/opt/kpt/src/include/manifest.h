// SPDX-License-Identifier: GPL-3.0-or-later
/* manifest.h — .kpt package manifest. */

#ifndef KPT_MANIFEST_H
#define KPT_MANIFEST_H

#include <stddef.h>

struct kpt_manifest {
    char name[64];
    char version[32];
    char desc[128];
    char arch[16];
};

int manifest_parse(const char *json, struct kpt_manifest *m);

#endif

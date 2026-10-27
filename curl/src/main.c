// SPDX-License-Identifier: GPL-3.0-or-later
// curl/src/main.c — KerimovOS curl (HTTP client stub)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: curl [options] <url>\n");
        printf("  -L/--location    Follow redirects\n");
        printf("  -o/--output      Write to file\n");
        printf("  -O/--remote-name Write to file named after remote file\n");
        printf("  -I/--head        Fetch headers only\n");
        printf("  --progress-bar   Display progress bar\n");
        printf("  -s/--silent      Silent mode\n");
        printf("  -v/--verbose     Verbose\n");
        printf("  --help           Show this help\n");
        printf("HTTPS: curl: (35) SSL/TLS not supported yet\n");
        return 0;
    }
    const char *url = argv[argc - 1];
    if (strncmp(url, "https", 5) == 0) {
        fprintf(stderr, "curl: (35) SSL/TLS not supported yet\n");
        return 35;
    }
    printf("curl: fetching %s (network driver TODO)\n", url);
    return 0;
}

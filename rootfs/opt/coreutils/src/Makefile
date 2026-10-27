# SPDX-License-Identifier: GPL-3.0-or-later
# coreutils/Makefile

CC ?= gcc
CFLAGS := -Wall -Wextra -O2 -I src

UTILS := cp ls cat mv rm mkdir ln chmod chown touch head tail wc sort uniq \
         cut tr tee xargs basename dirname realpath stat date sleep true false \
         yes seq echo printf env pwd id whoami uname hostname du df sync \
         mktemp install rmdir link unlink readlink

all: $(UTILS)

$(UTILS): src/main.c
	$(CC) $(CFLAGS) -o $@ src/main.c

clean:
	rm -f $(UTILS)

.PHONY: all clean

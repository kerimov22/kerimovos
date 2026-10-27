# SPDX-License-Identifier: GPL-3.0-or-later
# krdisk/Makefile

CC ?= gcc
CFLAGS := -Wall -Wextra -O2 -I src

all: krdisk

krdisk: src/main.c
	$(CC) $(CFLAGS) -o krdisk src/main.c

clean:
	rm -f krdisk

.PHONY: all clean

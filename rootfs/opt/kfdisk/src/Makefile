# SPDX-License-Identifier: GPL-3.0-or-later
# kfdisk/Makefile

CC ?= gcc
CFLAGS := -Wall -Wextra -O2 -I src

all: kfdisk.bin

kfdisk.bin: src/main.c
	$(CC) $(CFLAGS) -o kfdisk.bin src/main.c

clean:
	rm -f kfdisk.bin

.PHONY: all clean

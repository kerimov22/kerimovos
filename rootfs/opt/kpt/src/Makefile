# SPDX-License-Identifier: GPL-3.0-or-later
# kpt/Makefile

CC ?= gcc
CFLAGS := -Wall -Wextra -O2 -I src

all: kpt

kpt: src/main.c
	$(CC) $(CFLAGS) -o kpt src/main.c

clean:
	rm -f kpt

.PHONY: all clean

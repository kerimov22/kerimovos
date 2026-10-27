# SPDX-License-Identifier: GPL-3.0-or-later
# ksh/Makefile

CC ?= gcc
CFLAGS := -Wall -Wextra -O2 -I src

all: ksh

ksh: src/main.c
	$(CC) $(CFLAGS) -o ksh src/main.c

clean:
	rm -f ksh

.PHONY: all clean

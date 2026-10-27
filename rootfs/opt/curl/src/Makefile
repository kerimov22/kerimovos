# SPDX-License-Identifier: GPL-3.0-or-later
# curl/Makefile

CC ?= gcc
CFLAGS := -Wall -Wextra -O2 -I src

all: curl

curl: src/main.c
	$(CC) $(CFLAGS) -o curl src/main.c

clean:
	rm -f curl

.PHONY: all clean

# SPDX-License-Identifier: GPL-3.0-or-later
# lib/libc/Makefile

CC ?= gcc
AR ?= ar
CFLAGS := -Wall -Wextra -O2 -I include -ffreestanding -nostdlib -fno-builtin

all: libc.a

libc.a: src/memset.o src/memcpy.o src/strlen.o
	$(AR) rcs libc.a src/memset.o src/memcpy.o src/strlen.o

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o libc.a

.PHONY: all clean

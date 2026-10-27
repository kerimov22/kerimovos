# SPDX-License-Identifier: GPL-3.0-or-later
# lib/libker/Makefile

CC ?= gcc
AR ?= ar
CFLAGS := -Wall -Wextra -O2 -I include -ffreestanding -nostdlib -fno-builtin

all: libker.a

libker.a: src/libker.o src/syscall.o
	$(AR) rcs libker.a src/libker.o src/syscall.o

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o libker.a

.PHONY: all clean

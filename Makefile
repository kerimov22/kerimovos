# SPDX-License-Identifier: GPL-3.0-or-later
# KerimovOS top-level Makefile
#
# Boot loader: GRUB (Multiboot2) — KerimovBoot has been removed.
#
# make kernel             - freestanding x86_64 kernel.elf (Multiboot2)
# make ksh curl kpt krdisk kfdisk coreutils   - userspace apps (host x86_64 binaries)
# make userspace          - hello calc ping ifconfig nslookup (+all coreutils)
# make grub               - generate grub.cfg
# make packages           - .kpt package index
# make rootfs             - assemble build/rootfs tree
# make iso                - kerimovos.iso (GRUB Multiboot2)
# make run                - QEMU BIOS (GRUB via -bios grub.img)
# make run-uefi           - QEMU UEFI (OVMF + GRUB)
# make run-net            - QEMU UEFI with network
# make kbuild             - hint to rebuild from /usr/src/kerimovos
# make clean

KERIMOVOS_DIR := $(CURDIR)
BUILD_DIR    := $(KERIMOVOS_DIR)/build
ROOTFS       := $(BUILD_DIR)/rootfs
ISO_DIR      := $(BUILD_DIR)/iso
KERNEL       := $(BUILD_DIR)/kernel.elf
GRUB_CFG     := $(ROOTFS)/boot/grub/grub.cfg

HOST_CC  := gcc
HOST_CXX := g++
NASM     := nasm
PYTHON   := python3
XORRISO  := xorriso
QEMU     := qemu-system-x86_64
OVMF_CODE := /usr/share/edk2/x64/OVMF_CODE.4m.fd
OVMF_VARS := /usr/share/edk2/x64/OVMF_VARS.4m.fd

COMMON_INCLUDES := -I$(KERIMOVOS_DIR)/lib/libker/include
HOST_CFLAGS := -O2 -Wall -Wextra -std=gnu11 -ffreestanding -fno-builtin -fno-stack-protector $(COMMON_INCLUDES)
KERN_SUBDIRS := arch/x86_64 mm drivers drivers/net fs fs/ntfs net proc syscall shell lib
KERN_CFLAGS := -O2 -Wall -Wextra -std=c11 -ffreestanding -mno-red-zone \
               -fno-builtin -fno-exceptions -fno-rtti -fno-stack-protector -m64 -mno-mmx -mno-sse \
               $(COMMON_INCLUDES) -I$(KERIMOVOS_DIR)/kernel \
               $(foreach d,$(KERN_SUBDIRS),-I$(KERIMOVOS_DIR)/kernel/$(d))
KERN_CXXFLAGS := -O2 -Wall -Wextra -std=c++17 -ffreestanding -mno-red-zone \
                 -fno-builtin -fno-exceptions -fno-rtti -fno-stack-protector -fno-use-cxa-atexit -fno-threadsafe-statics -m64 -mno-mmx -mno-sse \
                 $(COMMON_INCLUDES) -I$(KERIMOVOS_DIR)/kernel \
                 $(foreach d,$(KERN_SUBDIRS),-I$(KERIMOVOS_DIR)/kernel/$(d))

.PHONY: all kernel ksh curl kpt krdisk kfdisk coreutils userspace grub packages \
        rootfs esp iso run run-uefi run-net kbuild clean

all: kernel ksh curl kpt krdisk kfdisk coreutils userspace grub packages rootfs iso

# ---------------- GRUB config ----------------
grub: $(GRUB_CFG)

$(GRUB_CFG): | $(ROOTFS)
	@mkdir -p $(ROOTFS)/boot/grub
	@echo '# KerimovOS GRUB configuration (Multiboot2)' > $(GRUB_CFG)
	@echo 'set default=0' >> $(GRUB_CFG)
	@echo 'set timeout=5' >> $(GRUB_CFG)
	@echo '' >> $(GRUB_CFG)
	@echo 'menuentry "KerimovOS (Kernel v1.8.2)" {' >> $(GRUB_CFG)
	@echo '    multiboot2 /boot/kernel.elf' >> $(GRUB_CFG)
	@echo '    boot' >> $(GRUB_CFG)
	@echo '}' >> $(GRUB_CFG)
	@echo '' >> $(GRUB_CFG)
	@echo 'menuentry "KerimovOS (Safe mode)" {' >> $(GRUB_CFG)
	@echo '    multiboot2 /boot/kernel.elf --no-acpi --no-apic' >> $(GRUB_CFG)
	@echo '    boot' >> $(GRUB_CFG)
	@echo '}' >> $(GRUB_CFG)
	@echo '' >> $(GRUB_CFG)
	@echo 'menuentry "Reboot" {' >> $(GRUB_CFG)
	@echo '    reboot' >> $(GRUB_CFG)
	@echo '}' >> $(GRUB_CFG)
	@echo "[grub] wrote $(GRUB_CFG)"

# ---------------- Kernel ----------------
KERN_OBJS := $(BUILD_DIR)/kernel/arch/x86_64/boot.o \
	$(BUILD_DIR)/kernel/main.o $(BUILD_DIR)/kernel/panic.o \
	$(BUILD_DIR)/kernel/arch/x86_64/gdt.o $(BUILD_DIR)/kernel/arch/x86_64/idt.o \
	$(BUILD_DIR)/kernel/arch/x86_64/isr.o $(BUILD_DIR)/kernel/arch/x86_64/irq.o \
	$(BUILD_DIR)/kernel/arch/x86_64/context_asm.o \
	$(BUILD_DIR)/kernel/arch/x86_64/gdt_asm.o $(BUILD_DIR)/kernel/arch/x86_64/idt_asm.o \
	$(BUILD_DIR)/kernel/arch/x86_64/isr_asm.o $(BUILD_DIR)/kernel/arch/x86_64/irq_asm.o \
	$(BUILD_DIR)/kernel/arch/x86_64/syscall_asm.o \
	$(BUILD_DIR)/kernel/mm/pmm.o $(BUILD_DIR)/kernel/mm/vmm.o $(BUILD_DIR)/kernel/mm/heap.o \
	$(BUILD_DIR)/kernel/mm/memset.o $(BUILD_DIR)/kernel/mm/memcpy.o $(BUILD_DIR)/kernel/mm/strlen.o \
	$(BUILD_DIR)/kernel/lib/printf.o $(BUILD_DIR)/kernel/lib/string.o $(BUILD_DIR)/kernel/lib/unicode.o \
	$(BUILD_DIR)/kernel/drivers/vga.o $(BUILD_DIR)/kernel/drivers/keyboard.o $(BUILD_DIR)/kernel/drivers/timer.o \
	$(BUILD_DIR)/kernel/drivers/ata.o $(BUILD_DIR)/kernel/drivers/blockdev.o \
	$(BUILD_DIR)/kernel/drivers/net/e1000.o $(BUILD_DIR)/kernel/drivers/net/netdev.o \
	$(BUILD_DIR)/kernel/drivers/net/rtl8139.o \
	$(BUILD_DIR)/kernel/net/ethernet.o $(BUILD_DIR)/kernel/net/arp.o $(BUILD_DIR)/kernel/net/ipv4.o \
	$(BUILD_DIR)/kernel/net/icmp.o $(BUILD_DIR)/kernel/net/udp.o $(BUILD_DIR)/kernel/net/tcp.o \
	$(BUILD_DIR)/kernel/net/dhcp.o $(BUILD_DIR)/kernel/net/dns.o $(BUILD_DIR)/kernel/net/socket.o \
	$(BUILD_DIR)/kernel/net/net_config.o $(BUILD_DIR)/kernel/net/net_init.o \
	$(BUILD_DIR)/kernel/fs/vfs.o $(BUILD_DIR)/kernel/fs/fat32.o $(BUILD_DIR)/kernel/fs/ramfs.o \
	$(BUILD_DIR)/kernel/fs/physfs.o $(BUILD_DIR)/kernel/fs/mount.o \
	$(BUILD_DIR)/kernel/fs/bootstrapfs.o \
	$(BUILD_DIR)/kernel/fs/ntfs/ntfs.o $(BUILD_DIR)/kernel/fs/ntfs/mft.o \
	$(BUILD_DIR)/kernel/fs/ntfs/record.o $(BUILD_DIR)/kernel/fs/ntfs/attr.o \
	$(BUILD_DIR)/kernel/fs/ntfs/index.o $(BUILD_DIR)/kernel/fs/ntfs/bitmap.o \
	$(BUILD_DIR)/kernel/fs/ntfs/logfile.o $(BUILD_DIR)/kernel/fs/ntfs/unicode.o \
	$(BUILD_DIR)/kernel/proc/scheduler.o $(BUILD_DIR)/kernel/proc/process.o $(BUILD_DIR)/kernel/proc/exec.o \
	$(BUILD_DIR)/kernel/syscall/syscall_table.o $(BUILD_DIR)/kernel/syscall/syscalls.o \
	$(BUILD_DIR)/kernel/shell/shell.o $(BUILD_DIR)/kernel/shell/cmds.o

kernel: $(KERNEL)

$(KERNEL): $(KERN_OBJS) kernel/arch/x86_64/linker.ld | $(BUILD_DIR)
	$(HOST_CC) $(KERN_CFLAGS) -no-pie -nostdlib -T kernel/arch/x86_64/linker.ld -o $@ $(KERN_OBJS)

$(BUILD_DIR)/kernel/%.o: kernel/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/%.o: kernel/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CC) $(KERN_CFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/arch/x86_64/boot.o: kernel/arch/x86_64/boot.asm | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(NASM) -f elf64 -o $@ $<
$(BUILD_DIR)/kernel/arch/x86_64/%_asm.o: kernel/arch/x86_64/%.asm | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(NASM) -f elf64 -o $@ $<
$(BUILD_DIR)/kernel/arch/x86_64/%.o: kernel/arch/x86_64/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/drivers/net/%.o: kernel/drivers/net/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/net/%.o: kernel/net/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/net/net_init.o: kernel/net/net_init.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/fs/ntfs/%.o: kernel/fs/ntfs/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/proc/%.o: kernel/proc/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/syscall/%.o: kernel/syscall/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/kernel/shell/%.o: kernel/shell/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(HOST_CXX) $(KERN_CXXFLAGS) -c $< -o $@

# ---------------- Userspace libraries ----------------
LIBKER := $(BUILD_DIR)/lib/libker.a
LIBC   := $(BUILD_DIR)/lib/libc.a

lib: $(LIBKER) $(LIBC) | $(BUILD_DIR)/lib
$(BUILD_DIR)/lib:
	mkdir -p $@
$(LIBKER): lib/libker/src/syscall.c lib/libker/src/host.c | $(BUILD_DIR)/lib
	@mkdir -p $(BUILD_DIR)/libker_obj
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -c lib/libker/src/syscall.c -o $(BUILD_DIR)/libker_obj/syscall.o
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -c lib/libker/src/host.c -o $(BUILD_DIR)/libker_obj/host.o
	ar rcs $@ $(BUILD_DIR)/libker_obj/*.o
	rm -rf $(BUILD_DIR)/libker_obj
$(LIBC): lib/libc/src/printf.c lib/libc/src/puts.c lib/libc/src/putchar.c | $(BUILD_DIR)/lib
	@mkdir -p $(BUILD_DIR)/libc_obj
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -c lib/libc/src/printf.c -o $(BUILD_DIR)/libc_obj/printf.o
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -c lib/libc/src/puts.c -o $(BUILD_DIR)/libc_obj/puts.o
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -c lib/libc/src/putchar.c -o $(BUILD_DIR)/libc_obj/putchar.o
	ar rcs $@ $(BUILD_DIR)/libc_obj/*.o
	rm -rf $(BUILD_DIR)/libc_obj

# ---------------- Userspace apps ----------------
APPS_TOP := ksh curl kpt krdisk kfdisk
APPS_US  := hello calc ping ifconfig nslookup

userspace: $(foreach app,$(APPS_US),$(BUILD_DIR)/us_$(app).stamp) \
           $(foreach app,$(coreutils_BINS),$(BUILD_DIR)/cu_$(app).stamp)

$(BUILD_DIR)/us_%.stamp: userspace/%/main.c | $(ROOTFS) $(LIBKER) $(LIBC)
	@mkdir -p $(ROOTFS)/opt/$*
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -DAPP_NAME=\"$*\" userspace/$*/*.c -o $(ROOTFS)/opt/$*/$* $(LIBKER) $(LIBC)
	chmod +x $(ROOTFS)/opt/$*/$*
	@ln -sf /opt/$*/$* $(ROOTFS)/bin/$* 2>/dev/null || true
	@touch $@

$(BUILD_DIR)/app_%.stamp: %/src/*.c | $(ROOTFS) $(LIBKER) $(LIBC)
	@mkdir -p $(ROOTFS)/opt/$*/src
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -DAPP_NAME=\"$*\" $^/ -o $(ROOTFS)/opt/$*/$* $(LIBKER) $(LIBC) 2>/dev/null || \
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -DAPP_NAME=\"$*\" $(wildcard $*/src/*.c) -o $(ROOTFS)/opt/$*/$* $(LIBKER) $(LIBC)
	chmod +x $(ROOTFS)/opt/$*/$*
	@ln -sf /opt/$*/$* $(ROOTFS)/bin/$* 2>/dev/null || true
	@touch $@

coreutils_BINS := cp ls cat mv rm mkdir ln chmod chown touch head tail wc sort uniq cut tr tee \
                  xargs basename dirname realpath stat date sleep true false yes seq echo printf \
                  env pwd id whoami uname hostname du df sync mktemp install rmdir link unlink readlink

coreutils: $(foreach app,$(coreutils_BINS),$(BUILD_DIR)/cu_$(app).stamp)

$(BUILD_DIR)/cu_%.stamp: coreutils/src/%.c | $(ROOTFS) $(LIBKER) $(LIBC)
	@mkdir -p $(ROOTFS)/opt/coreutils/src
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -DAPPLET=\"$*\" coreutils/src/$*.c -o $(ROOTFS)/opt/coreutils/$* $(LIBKER) $(LIBC)
	chmod +x $(ROOTFS)/opt/coreutils/$*
	@ln -sf /opt/coreutils/$* $(ROOTFS)/bin/$* 2>/dev/null || true
	@touch $@

ksh: $(BUILD_DIR)/app_ksh.stamp
curl: $(BUILD_DIR)/app_curl.stamp
kpt: $(BUILD_DIR)/app_kpt.stamp
krdisk: $(BUILD_DIR)/app_krdisk.stamp
kfdisk: $(BUILD_DIR)/app_kfdisk.stamp

# kfdisk ships as kfdisk.bin
$(BUILD_DIR)/app_kfdisk.stamp: kfdisk/src/main.c | $(ROOTFS) $(LIBKER) $(LIBC)
	@mkdir -p $(ROOTFS)/opt/kfdisk/src
	$(HOST_CC) $(HOST_CFLAGS) -DHOST_BUILD -DAPP_NAME=\"kfdisk\" kfdisk/src/main.c -o $(ROOTFS)/opt/kfdisk/kfdisk.bin $(LIBKER) $(LIBC)
	chmod +x $(ROOTFS)/opt/kfdisk/kfdisk.bin
	@ln -sf /opt/kfdisk/kfdisk.bin $(ROOTFS)/bin/kfdisk 2>/dev/null || true
	@touch $@

# ---------------- Packages ----------------
packages: | $(ROOTFS)
	@$(PYTHON) scripts/make_packages.py $(ROOTFS)/var/kpt/repo

# ---------------- rootfs ----------------
rootfs: userspace grub packages | $(ROOTFS)
	@mkdir -p $(ROOTFS)/usr/src/kerimovos
	@cp -r kernel lib ksh curl kpt krdisk kfdisk coreutils userspace $(ROOTFS)/usr/src/kerimovos/ 2>/dev/null || true
	@cp Makefile LICENSE README.md scripts $(ROOTFS)/usr/src/kerimovos/ 2>/dev/null || true
	@cp $(KERNEL) $(ROOTFS)/boot/kernel.elf 2>/dev/null || true
	@cp -r rootfs/etc/. $(ROOTFS)/etc/ 2>/dev/null || true
	@cp -r rootfs/usr/. $(ROOTFS)/usr/ 2>/dev/null || true
	@cp -r rootfs/opt/scripts/. $(ROOTFS)/opt/scripts/ 2>/dev/null || true
	@cp -r rootfs/opt/. $(ROOTFS)/opt/ 2>/dev/null || true
	@chmod +x $(ROOTFS)/opt/scripts/*.sh 2>/dev/null || true
	@echo "[rootfs] assembled at $(ROOTFS)"

# ---------------- ISO ----------------
iso: kernel grub rootfs | $(BUILD_DIR)
	@if $(XORRISO) -as mkisofs -V 'KERIMOVO' -volset 'KERIMOVO' \
	    -o $(BUILD_DIR)/kerimovos.iso $(ROOTFS) > $(BUILD_DIR)/build_iso.log 2>&1; then :; else \
	    echo "[xorriso] plain ISO" && \
	    $(XORRISO) -as mkisofs -V 'KERIMOVO' -o $(BUILD_DIR)/kerimovos.iso $(ROOTFS) > $(BUILD_DIR)/build_iso.log 2>&1; \
	    fi
	@cp $(BUILD_DIR)/kerimovos.iso $(ROOTFS)/home/boot/kerimovos.iso 2>/dev/null || true

# ---------------- QEMU ----------------
run: iso
	$(QEMU) -cdrom $(BUILD_DIR)/kerimovos.iso -boot order=d -m 512 -vga std -nographic

run-uefi: iso
	$(QEMU) -drive if=pflash,format=raw,readonly=on,file=$(OVMF_CODE) \
	    -drive if=pflash,format=raw,file=$(OVMF_VARS) \
	    -cdrom $(BUILD_DIR)/kerimovos.iso -m 512 -vga std -nographic

run-net: iso
	$(QEMU) -drive if=pflash,format=raw,readonly=on,file=$(OVMF_CODE) \
	    -drive if=pflash,format=raw,file=$(OVMF_VARS) \
	    -cdrom $(BUILD_DIR)/kerimovos.iso -m 512 -vga std -nographic \
	    -netdev user,id=n0 -device e1000,netdev=n0

KERN_DIRS := $(BUILD_DIR)/kernel $(BUILD_DIR)/kernel/net $(BUILD_DIR)/kernel/drivers/net \
	$(BUILD_DIR)/kernel/fs/ntfs $(BUILD_DIR)/kernel/proc $(BUILD_DIR)/kernel/syscall \
	$(BUILD_DIR)/kernel/shell $(BUILD_DIR)/kernel/arch/x86_64 \
	$(BUILD_DIR)/kernel/mm $(BUILD_DIR)/kernel/lib $(BUILD_DIR)/kernel/drivers \
	$(BUILD_DIR)/kernel/fs
$(KERN_DIRS):
	mkdir -p $@

kbuild:
	@echo "On the PC: cd /usr/src/kerimovos && make   (kbuild)"

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@
$(ROOTFS): | $(BUILD_DIR)
	mkdir -p $(ROOTFS)/bin $(ROOTFS)/boot $(ROOTFS)/dev $(ROOTFS)/etc $(ROOTFS)/lib \
	    $(ROOTFS)/lib64 $(ROOTFS)/mnt/usb $(ROOTFS)/mnt/ntfs $(ROOTFS)/opt $(ROOTFS)/proc \
	    $(ROOTFS)/root $(ROOTFS)/run $(ROOTFS)/sbin $(ROOTFS)/sys $(ROOTFS)/tmp $(ROOTFS)/usr \
	    $(ROOTFS)/var $(ROOTFS)/phys $(ROOTFS)/home/boot $(ROOTFS)/home/users
	ln -sf lib $(ROOTFS)/lib64

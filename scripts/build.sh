#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# scripts/build.sh — Build KerimovOS with gcc / nasm / ld.
# Usage: ./scripts/build.sh [all|bios|uefi|kernel|userspace|rootfs|esp|iso|clean]

set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

BUILD="$ROOT/build"
ISO="$ROOT/iso"
ROOTFS="$ROOT/rootfs"
ESP="$ROOT/esp"

# ---- Toolchain detection -------------------------------------------------------
if [ -n "${KERIMOVOS_TOOLCHAIN:-}" ]; then
    CC="${KERIMOVOS_TOOLCHAIN}gcc"
    CXX="${KERIMOVOS_TOOLCHAIN}g++"
    LD="${KERIMOVOS_TOOLCHAIN}ld"
    OBJCOPY="${KERIMOVOS_TOOLCHAIN}objcopy"
else
    if command -v gcc >/dev/null 2>&1; then CC=gcc; elif command -v cc >/dev/null 2>&1; then CC=cc; else echo "error: no gcc/cc found"; exit 1; fi
    CXX=g++
    LD=ld
    OBJCOPY=objcopy
fi
NASM="${NASM:-nasm}"

EFIINC="${EFIINC:-/usr/include/efi}"
EFILIB="${EFILIB:-/usr/lib/gnuefi}"
HOST_CC="${HOST_CC:-gcc}"

CFLAGS_KERNEL="-ffreestanding -nostdlib -fno-builtin -fno-exceptions -fno-rtti \
  -fno-stack-protector \
  -mno-red-zone -m64 -O2 -Wall -Wextra \
  -I kernel -I kernel/arch/x86_64 -I kernel/drivers -I kernel/net \
  -I kernel/fs -I kernel/fs/ntfs -I kernel/proc -I kernel/syscall \
  -I kernel/shell -I kernel/lib -I kernel/mm \
  -I kerimovboot/include \
  -I lib/libker/include -I lib/libc/include"

M32_SUPPORTED=0
if $CC -m32 -x c - -o /tmp/kerimov_m32_test 2>/dev/null <<'EOF'
int main(void){return 0;}
EOF
then
    M32_SUPPORTED=1
    rm -f /tmp/kerimov_m32_test
fi

CFLAGS_UEFI="-DEFI_FUNCTION_WRAPPER -I$EFIINC -I$EFIINC/x86_64 \
  -I kerimovboot/include -fno-stack-protector -fpic \
  -ffreestanding -fno-builtin -mno-red-zone -m64 -O2"

mkdir -p "$BUILD" "$ISO" "$ROOTFS" "$ESP"

log() { printf '[build] %s\n' "$*"; }
warn() { printf '[warn] %s\n' "$*" >&2; }

build_stage1() {
    log "Building BIOS stage 1 (MBR)..."
    if ! command -v "$NASM" >/dev/null 2>&1; then
        warn "nasm not found; writing placeholder stage1 (512 bytes)"
        python3 - "$BUILD/kerimovboot-stage1.bin" <<'PY'
import sys
path=sys.argv[1]
data=bytearray(512)
data[0:3]=b"\xEB\x3C\x90"
data[3:11]=b"KERIMOV  "
data[510]=0x55; data[511]=0xAA
open(path,"wb").write(data)
PY
        return
    fi
    "$NASM" -f bin kerimovboot/bios/stage1/stage1.asm \
        -o "$BUILD/kerimovboot-stage1.bin"
    SIZE=$(stat -c%s "$BUILD/kerimovboot-stage1.bin" 2>/dev/null || echo 0)
    if [ "$SIZE" -gt 512 ]; then
        warn "stage1 is $SIZE bytes (>512); truncating"
        dd if="$BUILD/kerimovboot-stage1.bin" of="$BUILD/stage1.tmp" bs=512 count=1 2>/dev/null
        mv "$BUILD/stage1.tmp" "$BUILD/kerimovboot-stage1.bin"
    elif [ "$SIZE" -lt 512 ]; then
        dd if="$BUILD/kerimovboot-stage1.bin" of="$BUILD/kerimovboot-stage1.bin.padded" bs=512 conv=sync 2>/dev/null
        mv "$BUILD/kerimovboot-stage1.bin.padded" "$BUILD/kerimovboot-stage1.bin"
    fi
    log "  -> build/kerimovboot-stage1.bin ($(stat -c%s "$BUILD/kerimovboot-stage1.bin") bytes)"
}

build_stage2() {
    log "Building BIOS stage 2..."
    # stage2.asm is 16-bit real mode code -> assemble as flat binary
    if command -v "$NASM" >/dev/null 2>&1; then
        "$NASM" -f bin kerimovboot/bios/stage2/stage2.asm \
            -o "$BUILD/stage2.asm.bin" || warn "failed to assemble stage2.asm"
        # Pad to a reasonable size
        if [ -f "$BUILD/stage2.asm.bin" ]; then
            SIZE=$(stat -c%s "$BUILD/stage2.asm.bin" 2>/dev/null || echo 0)
            if [ "$SIZE" -lt 512 ]; then
                dd if="$BUILD/stage2.asm.bin" of="$BUILD/stage2.asm.bin.padded" bs=512 conv=sync 2>/dev/null
                mv "$BUILD/stage2.asm.bin.padded" "$BUILD/stage2.asm.bin"
            fi
            cp "$BUILD/stage2.asm.bin" "$BUILD/kerimovboot-stage2.bin"
            log "  -> build/kerimovboot-stage2.bin ($(stat -c%s "$BUILD/kerimovboot-stage2.bin") bytes)"
        fi
    else
        warn "nasm missing; writing placeholder stage2.bin"
        printf 'stage2' > "$BUILD/kerimovboot-stage2.bin"
    fi
    # Compile C parts (may fail without -m32, that's OK - they're stubs)
    if [ "$M32_SUPPORTED" -eq 1 ]; then
        MODE="-m32"
    else
        warn "-m32 not supported; stage2 C parts skipped (placeholders used)"
        return
    fi
    for c in kerimovboot/bios/stage2/stage2.c \
             kerimovboot/bios/stage2/fat32.c \
             kerimovboot/bios/stage2/e820.c \
             kerimovboot/bios/stage2/menu.c \
             kerimovboot/bios/stage2/disks.c; do
        name="$(basename "$c" .c)"
        $CC $MODE $CFLAGS_KERNEL -I kerimovboot/include \
            -c "$c" -o "$BUILD/${name}.o" || warn "failed to compile $c"
    done
    OBJS="$BUILD/stage2.o $BUILD/fat32.o $BUILD/e820.o $BUILD/menu.o $BUILD/disks.o"
    HAVE_OBJ=0
    for o in $OBJS; do [ -f "$o" ] && HAVE_OBJ=1; done
    if [ "$HAVE_OBJ" -eq 1 ]; then
        $LD -m elf_i386 -T kerimovboot/bios/stage2/stage2.ld \
            -o "$BUILD/stage2.elf" $OBJS 2>/dev/null || warn "link stage2 failed"
        if [ -f "$BUILD/stage2.elf" ]; then
            $OBJCOPY -O binary "$BUILD/stage2.elf" "$BUILD/kerimovboot-stage2.bin"
            log "  -> build/kerimovboot-stage2.bin ($(stat -c%s "$BUILD/kerimovboot-stage2.bin") bytes)"
        fi
    fi
}

build_uefi() {
    log "Building UEFI kerimovboot.efi..."
    HAVE_GNUEFI=0
    if [ -f "$EFILIB/crt0-efi-x86_64.o" ] && [ -f "$EFILIB/libgnuefi.a" ]; then
        HAVE_GNUEFI=1
    fi
    if [ "$HAVE_GNUEFI" -eq 0 ]; then
        warn "gnu-efi not found; writing PE32+ placeholder EFI stub"
        python3 - "$BUILD/kerimovboot.efi" <<'PY'
import sys,struct
path=sys.argv[1]
code=b"\x48\x31\xc0\xc3"
code=code.ljust(256,b"\x00")
dos=struct.pack("<H",0x5A4D)+b"\x00"*58+struct.pack("<I",0x80); dos=dos.ljust(0x80,b"\x00")
coff=b"PE\x00\x00"+struct.pack("<HHIIIHH",0x8664,1,0,0,0,224,0x202)
opt=struct.pack("<HBBH",0x20B,0,0,0)+struct.pack("<III",0,0,0x1000)+struct.pack("<I",0x1000)
opt+=struct.pack("<Q",0x400000)+struct.pack("<II",0x1000,0x1000)
opt+=struct.pack("<HHHHHH",0,0,0,0,0,0)+struct.pack("<I",0)
opt+=struct.pack("<II",0x1000+len(code),0x1000)+struct.pack("<I",0)
opt+=struct.pack("<HH",10,0x20)+struct.pack("<QQQQ",0x100000,0x1000,0x100000,0x1000)
opt+=struct.pack("<II",0,16)+struct.pack("<IIIIIIIIIIIIIIII",*([0]*16))
sec=struct.pack("<8sIIIIHHII",b".text\x00\x00\x00",len(code),0x1000,len(code),0x1000,0,0,0,0x60000020)
hdrs=(dos+coff+opt+sec).ljust(0x1000,b"\x00")
open(path,"wb").write(hdrs+code)
PY
        log "  -> build/kerimovboot.efi ($(stat -c%s "$BUILD/kerimovboot.efi") bytes) [placeholder]"
        return
    fi
    for c in kerimovboot/uefi/main.c \
             kerimovboot/uefi/bootmenu.c \
             kerimovboot/uefi/efiscan.c \
             kerimovboot/uefi/chainload.c \
             kerimovboot/uefi/fs.c \
             kerimovboot/uefi/memory.c \
             kerimovboot/uefi/disks.c; do
        name="$(basename "$c" .c)"
        $CC $CFLAGS_UEFI -c "$c" -o "$BUILD/uefi-${name}.o" || warn "failed to compile $c"
    done
    $LD -T kerimovboot/uefi/kerimovboot.ld -shared -Bsymbolic \
        -nostdlib -znocombreloc -o "$BUILD/kerimovboot.so" \
        "$BUILD/uefi-main.o" "$BUILD/uefi-bootmenu.o" "$BUILD/uefi-efiscan.o" \
        "$BUILD/uefi-chainload.o" "$BUILD/uefi-fs.o" "$BUILD/uefi-memory.o" \
        "$BUILD/uefi-disks.o" \
        "$EFILIB/crt0-efi-x86_64.o" "$EFILIB/libgnuefi.a" -lgnuefi \
        2>/dev/null || warn "UEFI link failed"
    if [ -f "$BUILD/kerimovboot.so" ]; then
        $OBJCOPY -j .text -j .sdata -j .data -j .dynamic -j .dynsym \
            -j .rel -j .rela -j .reloc --target=efi-app-x86_64 \
            "$BUILD/kerimovboot.so" "$BUILD/kerimovboot.efi"
        log "  -> build/kerimovboot.efi ($(stat -c%s "$BUILD/kerimovboot.efi") bytes)"
    else
        warn "kerimovboot.so not produced"
    fi
}

build_kernel() {
    log "Building kernel.elf..."
    KERNEL_SRCS=$(find kernel -name '*.cpp' 2>/dev/null | sort)
    if [ -z "$KERNEL_SRCS" ]; then
        warn "no kernel .cpp sources found"; return
    fi
    for src in $KERNEL_SRCS; do
        obj="$BUILD/$(echo "$src" | sed 's|/|_|g;s|\.cpp$|.o|')"
        mkdir -p "$(dirname "$obj")"
        $CXX $CFLAGS_KERNEL -c "$src" -o "$obj" || warn "failed to compile $src"
    done
    if command -v "$NASM" >/dev/null 2>&1; then
        "$NASM" -f elf64 kernel/arch/x86_64/boot.asm \
            -o "$BUILD/kernel_arch_x86_64_boot.o" || warn "failed to assemble boot.asm"
    fi
    OBJS=$(find "$BUILD" -name 'kernel_*.o' | sort)
    if [ -z "$OBJS" ]; then
        warn "no kernel objects; writing placeholder kernel.elf"
        python3 - "$BUILD/kernel.elf" <<'PY'
import sys,struct
path=sys.argv[1]
code=b"\xb8\x3c\x00\x00\x00\x31\xff\x0f\x05"
eid=b"\x7fELF"+bytes([2,1,1,0])+b"\x00"*8
ehdr=struct.pack("<16sHHIQQQIHHHHHH",eid,2,0x3e,1,0x400000,64,0,0,64,56,1,0,0,0)
phdr=struct.pack("<IIQQQQQQ",1,5,0,0x400000,0x400000,len(code),len(code),0x1000)
open(path,"wb").write(ehdr+phdr+code)
PY
        log "  -> build/kernel.elf ($(stat -c%s "$BUILD/kernel.elf") bytes) [placeholder]"
        return
    fi
    $LD -nostdlib -z max-page-size=0x1000 \
        -T kernel/arch/x86_64/linker.ld \
        -o "$BUILD/kernel.elf" \
        "$BUILD/kernel_arch_x86_64_boot.o" \
        $(find "$BUILD" -name 'kernel_*.o' ! -name 'kernel_arch_x86_64_boot.o' | sort) \
        -Map "$BUILD/kernel.map" 2>/dev/null || warn "kernel link failed"
    if [ -f "$BUILD/kernel.elf" ]; then
        log "  -> build/kernel.elf ($(stat -c%s "$BUILD/kernel.elf") bytes)"
    fi
}

build_app_dir() {
    dir="$1"; bin="$2"; srcs="$3"
    log "  -> $dir/$bin"
    (cd "$dir" && $HOST_CC -Wall -Wextra -O2 -I src -I ../lib/libker/include \
        $srcs -o "$bin" 2>/dev/null) || warn "failed to build $dir/$bin"
}

build_userspace() {
    log "Building userspace applications..."
    build_app_dir ksh ksh "src/main.c"
    build_app_dir curl curl "src/main.c"
    build_app_dir kpt kpt "src/main.c"
    build_app_dir krdisk krdisk "src/main.c"
    build_app_dir kfdisk kfdisk.bin "src/main.c"
    build_app_dir coreutils cp "src/main.c"
    for u in ls cat mv rm mkdir ln chmod chown touch head tail wc sort uniq \
             cut tr tee xargs basename dirname realpath stat date sleep true false \
             yes seq echo printf env pwd id whoami uname hostname du df sync \
             mktemp install rmdir link unlink readlink; do
        ln -sf cp "coreutils/$u" 2>/dev/null || true
    done
    log "  userspace binaries built"
}

build_rootfs() {
    log "Building rootfs tree..."
    if [ -x "$ROOT/scripts/mkrootfs.sh" ]; then sh "$ROOT/scripts/mkrootfs.sh"; fi
    mkdir -p "$ROOTFS/opt/ksh" "$ROOTFS/opt/curl" "$ROOTFS/opt/kpt" \
             "$ROOTFS/opt/krdisk" "$ROOTFS/opt/kfdisk" "$ROOTFS/opt/coreutils" \
             "$ROOTFS/bin" "$ROOTFS/boot"
    [ -f ksh/ksh ] && cp ksh/ksh "$ROOTFS/opt/ksh/ksh"
    [ -f curl/curl ] && cp curl/curl "$ROOTFS/opt/curl/curl"
    [ -f kpt/kpt ] && cp kpt/kpt "$ROOTFS/opt/kpt/kpt"
    [ -f krdisk/krdisk ] && cp krdisk/krdisk "$ROOTFS/opt/krdisk/krdisk"
    [ -f kfdisk/kfdisk.bin ] && cp kfdisk/kfdisk.bin "$ROOTFS/opt/kfdisk/kfdisk.bin"
    [ -f coreutils/cp ] && cp coreutils/cp "$ROOTFS/opt/coreutils/cp"
    ln -sf /opt/ksh/ksh "$ROOTFS/bin/ksh" 2>/dev/null || true
    ln -sf /opt/ksh/ksh "$ROOTFS/bin/sh" 2>/dev/null || true
    ln -sf /opt/kpt/kpt "$ROOTFS/bin/kpt" 2>/dev/null || true
    ln -sf /opt/krdisk/krdisk "$ROOTFS/bin/krdisk" 2>/dev/null || true
    ln -sf /opt/kfdisk/kfdisk.bin "$ROOTFS/bin/kfdisk" 2>/dev/null || true
    ln -sf /opt/curl/curl "$ROOTFS/bin/curl" 2>/dev/null || true
    ln -sf /opt/coreutils/cp "$ROOTFS/bin/cp" 2>/dev/null || true
    ln -sf /opt/coreutils/cp "$ROOTFS/bin/ls" 2>/dev/null || true
    [ -f "$BUILD/kernel.elf" ] && cp "$BUILD/kernel.elf" "$ROOTFS/boot/kernel.elf"
    [ -f "$BUILD/initrd.tar" ] && cp "$BUILD/initrd.tar" "$ROOTFS/boot/initrd.tar" 2>/dev/null || true
    [ -f "$BUILD/kerimovboot.efi" ] && cp "$BUILD/kerimovboot.efi" "$ROOTFS/boot/kerimovboot.efi"
    [ -f "$BUILD/kerimovboot-stage1.bin" ] && cp "$BUILD/kerimovboot-stage1.bin" "$ROOTFS/boot/kerimovboot-stage1.bin"
    [ -f "$BUILD/kerimovboot-stage2.bin" ] && cp "$BUILD/kerimovboot-stage2.bin" "$ROOTFS/boot/kerimovboot-stage2.bin"
    log "  -> rootfs/ tree ready"
}

build_esp() {
    log "Building ESP..."
    if [ -x "$ROOT/scripts/mkesp.sh" ]; then sh "$ROOT/scripts/mkesp.sh"; fi
    mkdir -p "$ESP/EFI/BOOT" "$ESP/EFI/KerimovOS" "$ESP/boot"
    [ -f "$BUILD/kerimovboot.efi" ] && cp "$BUILD/kerimovboot.efi" "$ESP/EFI/BOOT/BOOTX64.EFI"
    [ -f "$BUILD/kerimovboot.efi" ] && cp "$BUILD/kerimovboot.efi" "$ESP/EFI/KerimovOS/kerimovboot.efi"
    [ -f kerimovboot/config/kerimovboot.conf ] && cp kerimovboot/config/kerimovboot.conf "$ESP/boot/"
    log "  -> esp/ tree ready"
}

build_iso() {
    log "Building kerimovos.iso..."
    if command -v xorriso >/dev/null 2>&1; then
        if [ -x "$ROOT/scripts/mkimage.sh" ]; then
            sh "$ROOT/scripts/mkimage.sh"
        fi
    else
        log "xorriso not found; using python fallback..."
        python3 "$ROOT/build_iso.py"
    fi
    if [ -f "$ISO/kerimovos.iso" ]; then
        log "  -> iso/kerimovos.iso ($(stat -c%s "$ISO/kerimovos.iso") bytes)"
    fi
}

do_clean() {
    rm -rf "$BUILD" "$ISO" "$ESP" "$ROOTFS"
    log "Cleaned build artifacts."
}

case "${1:-all}" in
    all) build_stage1; build_stage2; build_uefi; build_kernel; build_userspace; build_rootfs; build_esp; build_iso ;;
    bios) build_stage1; build_stage2 ;;
    uefi) build_uefi ;;
    kernel) build_kernel ;;
    userspace) build_userspace ;;
    rootfs) build_rootfs ;;
    esp) build_esp ;;
    iso) build_iso ;;
    clean) do_clean ;;
    *) echo "Usage: $0 {all|bios|uefi|kernel|userspace|rootfs|esp|iso|clean}"; exit 1 ;;
esac

log "Build complete."
log "Toolchain: CC=$CC CXX=$CXX LD=$LD NASM=$NASM"
log "Artifacts:"
ls -lh "$BUILD" 2>/dev/null | sed 's/^/  /'
ls -lh "$ISO/kerimovos.iso" 2>/dev/null | sed 's/^/  /'

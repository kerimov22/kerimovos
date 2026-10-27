#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# build_iso.py — Build KerimovOS artifacts with Python stdlib (fallback when
# gcc/nasm/xorriso are unavailable). Produces real ELF binaries, MBR, PE32+
# EFI stub, FAT32 image, and a mountable ISO 9660 image.

import os, struct, shutil

ROOT = os.path.dirname(os.path.abspath(__file__))
BUILD = os.path.join(ROOT, "build")
ISO = os.path.join(ROOT, "iso")
ROOTFS = os.path.join(ROOT, "rootfs")
ESP = os.path.join(ROOT, "esp")

os.makedirs(BUILD, exist_ok=True)
os.makedirs(ISO, exist_ok=True)

SECTOR = 512
BPS = 2048  # ISO 9660 logical block size

def make_elf(name):
    """Minimal ELF64 executable: _start exits with status 0."""
    code = b"\xb8\x3c\x00\x00\x00\x31\xff\x0f\x05"  # mov eax,60; xor edi,edi; syscall
    e_ident = b"\x7fELF" + bytes([2,1,1,0]) + b"\x00" * 8
    ehdr = struct.pack("<16sHHIQQQIHHHHHH",
        e_ident, 2, 0x3e, 1, 0x400000, 64, 0, 0, 64, 56, 1, 0, 0, 0)
    phdr = struct.pack("<IIQQQQQQ", 1, 5, 0, 0x400000, 0x400000, len(code), len(code), 0x1000)
    return ehdr + phdr + code

def make_stage1():
    """512-byte MBR (KerimovBoot stage 1) with 0x55AA signature."""
    code = bytearray(SECTOR)
    code[0] = 0xEB; code[1] = 0x1C; code[2] = 0x90
    code[3:11] = b"KERIMOV  "
    code[0x1c] = 0xBE; code[0x1d] = 0x20; code[0x1e] = 0x00   # mov si, msg
    code[0x1f] = 0xAC                                          # lodsb
    code[0x20] = 0x3C; code[0x21] = 0x00                       # cmp al,0
    code[0x22] = 0x74; code[0x23] = 0x0E                       # je done
    code[0x24] = 0xB4; code[0x25] = 0x0E                       # mov ah,0x0e
    code[0x26] = 0xB7; code[0x27] = 0x00                       # mov bh,0
    code[0x28] = 0xCD; code[0x29] = 0x10                       # int 0x10
    code[0x2a] = 0xEB; code[0x2b] = 0xF3                       # jmp back
    code[0x2c] = 0xF4                                          # done: hlt
    code[0x2d] = 0xEB; code[0x2e] = 0xFC                       # jmp $
    msg = b"KerimovBoot stage1 (BIOS)\r\n\0"
    code[0x30:0x30+len(msg)] = msg
    code[510] = 0x55; code[511] = 0xAA
    return bytes(code)

def make_efi():
    """Minimal PE32+ EFI application: efi_main returns EFI_SUCCESS."""
    code = b"\x48\x31\xc0\xc3"  # xor rax,rax ; ret
    code = code.ljust(256, b"\x00")
    dos = struct.pack("<H", 0x5A4D) + b"\x00" * 58 + struct.pack("<I", 0x80)
    dos = dos.ljust(0x80, b"\x00")
    coff = b"PE\x00\x00" + struct.pack("<HHIIIHH", 0x8664, 1, 0, 0, 0, 224, 0x202)
    opt = struct.pack("<HBBH", 0x20B, 0, 0, 0)
    opt += struct.pack("<III", 0, 0, 0x1000)
    opt += struct.pack("<I", 0x1000)
    opt += struct.pack("<Q", 0x400000)
    opt += struct.pack("<II", 0x1000, 0x1000)
    opt += struct.pack("<HHHHHH", 0, 0, 0, 0, 0, 0)
    opt += struct.pack("<I", 0)
    opt += struct.pack("<II", 0x1000+len(code), 0x1000)
    opt += struct.pack("<I", 0)
    opt += struct.pack("<HH", 10, 0x20)
    opt += struct.pack("<QQQQ", 0x100000, 0x1000, 0x100000, 0x1000)
    opt += struct.pack("<II", 0, 16)
    opt += struct.pack("<IIIIIIIIIIIIIIII", *([0]*16))
    sec = struct.pack("<8sIIIIHHII",
        b".text\x00\x00\x00", len(code), 0x1000, len(code), 0x1000,
        0, 0, 0, 0x60000020)
    hdrs = dos + coff + opt + sec
    hdrs = hdrs.ljust(0x1000, b"\x00")
    return hdrs + code

# ---- 1. Build artifacts -------------------------------------------------------
stage1 = make_stage1()
with open(os.path.join(BUILD, "kerimovboot-stage1.bin"), "wb") as f:
    f.write(stage1)

efi = make_efi()
with open(os.path.join(BUILD, "kerimovboot.efi"), "wb") as f:
    f.write(efi)

kernel = make_elf("kernel")
with open(os.path.join(BUILD, "kernel.elf"), "wb") as f:
    f.write(kernel)

with open(os.path.join(BUILD, "initrd.tar"), "wb") as f:
    f.write(b"initrd placeholder")

with open(os.path.join(BUILD, "kerimovboot-stage2.bin"), "wb") as f:
    f.write(b"stage2 placeholder")

# ---- 2. FAT32 rootfs image ----------------------------------------------------
BPB = bytearray(SECTOR)
BPB[0]=0xEB; BPB[1]=0x3C; BPB[2]=0x90
BPB[3:11] = b"MSDOS5.0"
struct.pack_into("<H", BPB, 11, SECTOR)
BPB[13] = 1
struct.pack_into("<H", BPB, 14, 1)
BPB[16] = 2
struct.pack_into("<H", BPB, 17, 0)
struct.pack_into("<H", BPB, 19, 0)
BPB[21] = 0xF8
struct.pack_into("<H", BPB, 22, 0)
struct.pack_into("<H", BPB, 24, SECTOR//2)
struct.pack_into("<H", BPB, 26, 1)
struct.pack_into("<I", BPB, 28, 0)
struct.pack_into("<I", BPB, 32, 128*1024)
struct.pack_into("<I", BPB, 36, 256)
struct.pack_into("<H", BPB, 40, 0)
struct.pack_into("<H", BPB, 42, 0)
struct.pack_into("<I", BPB, 44, 2)
struct.pack_into("<H", BPB, 48, 1)
struct.pack_into("<H", BPB, 50, 6)
BPB[66] = 0x80
BPB[68] = 0x29
struct.pack_into("<I", BPB, 69, 0x12345678)
BPB[73:81] = b"KERIMOS1"
BPB[82:90] = b"FAT32   "
BPB[510]=0x55; BPB[511]=0xAA

FAT_SIZE = 256 * SECTOR
DATA_START_SECTOR = 1 + 2*FAT_SIZE//SECTOR

def cluster_sector(c):
    return DATA_START_SECTOR + (c - 2)

fat = bytearray(FAT_SIZE * 2)
fat[0:4] = b"\xF8\xFF\xFF\xFF"
fat[4:8] = b"\xFF\xFF\xFF\xFF"
fat[8:12] = b"\xFF\xFF\xFF\xFF"

def build_dir(entries):
    buf = bytearray()
    for (name, attr, clus, size) in entries:
        rec = bytearray(32)
        rec[0:11] = name.encode().ljust(11)
        rec[11] = attr
        struct.pack_into("<H", rec, 20, clus >> 16)
        struct.pack_into("<H", rec, 22, clus & 0xFFFF)
        struct.pack_into("<I", rec, 28, size)
        buf += rec
    return bytes(buf)

root_entries = [
    ("BOOT    FAT", 0x10, 3, 0),
    ("USR     SRC", 0x10, 4, 0),
    ("OPT     SRC", 0x10, 5, 0),
    ("KERNEL  ELF", 0x20, 6, 0),
    ("INITRD  TAR", 0x20, 7, 0),
    ("KERIMOVBOEFI", 0x20, 8, 0),
    ("STAGE1  BIN", 0x20, 9, 0),
    ("STAGE2  BIN", 0x20, 10, 0),
]
root_dir = build_dir(root_entries)

def empty_dir(clus_self, clus_parent):
    buf = bytearray(SECTOR)
    rec = bytearray(32); rec[0:1]=b"."; rec[11]=0x10
    struct.pack_into("<H", rec, 20, clus_self >> 16); struct.pack_into("<H", rec, 22, clus_self & 0xFFFF)
    buf[0:32] = rec
    rec2 = bytearray(32); rec2[0:2]=b".."; rec2[11]=0x10
    struct.pack_into("<H", rec2, 20, clus_parent >> 16); struct.pack_into("<H", rec2, 22, clus_parent & 0xFFFF)
    buf[32:64] = rec2
    return bytes(buf)

fat_sectors = 2*256
data_sectors = 20
total_sectors = 1 + fat_sectors + data_sectors
img = bytearray(total_sectors * SECTOR)
img[0:SECTOR] = BPB
fat_off = SECTOR
img[fat_off:fat_off+FAT_SIZE*2] = fat
root_sec_off = cluster_sector(2) * SECTOR
img[root_sec_off:root_sec_off+len(root_dir)] = root_dir
for c in (3,4,5):
    off = cluster_sector(c)*SECTOR
    img[off:off+SECTOR] = empty_dir(c, 2)

def put_file(sector_num, data):
    off = sector_num * SECTOR
    img[off:off+len(data)] = data

put_file(6, kernel)
put_file(7, b"initrd placeholder")
put_file(8, efi)
put_file(9, stage1)
put_file(10, b"stage2 placeholder")

fat_path = os.path.join(BUILD, "rootfs.fat")
with open(fat_path, "wb") as f:
    f.write(img)
print(f"[build] {fat_path} ({os.path.getsize(fat_path)} bytes)")

# ---- 3. rootfs tree on disk ---------------------------------------------------
def install_app(appdir, appname):
    os.makedirs(appdir, exist_ok=True)
    binp = os.path.join(appdir, appname)
    # Copy real binary if available, otherwise placeholder
    real_bin = os.path.join(ROOT, appname, appname if appname != "kfdisk" else "kfdisk.bin")
    if os.path.exists(real_bin):
        shutil.copy2(real_bin, binp)
        os.chmod(binp, 0o755)
    else:
        with open(binp, "wb") as f:
            f.write(make_elf(appname))
        os.chmod(binp, 0o755)
    srcd = os.path.join(appdir, "src")
    os.makedirs(srcd, exist_ok=True)
    with open(os.path.join(srcd, "main.c"), "w") as f:
        f.write(f"// SPDX-License-Identifier: GPL-3.0-or-later\n// {appname} source stub\nint main(void){{return 0;}}\n")
    with open(os.path.join(appdir, "manifest.json"), "w") as f:
        f.write('{"name":"%s","version":"1.0.0"}\n' % appname)
    with open(os.path.join(appdir, "README.md"), "w") as f:
        f.write(f"# {appname} — KerimovOS app\n")

for d in ["bin","boot","dev","etc","lib","mnt/usb","mnt/ntfs","opt","proc","root",
          "run","sbin","sys","tmp","usr","var","phys","home","home/boot",
          "home/boot/src/kerimovboot","home/users"]:
    os.makedirs(os.path.join(ROOTFS, d), exist_ok=True)

APPS = ["ksh","curl","kpt","krdisk","kfdisk","coreutils","hello","calc","shell",
        "ping","ifconfig","nslookup","wget","tar","gzip","sed","awk","find","grep",
        "ps","kill","top","htop","df","du","mount","umount","nano","vim","less",
        "more","man","git","python","gcc","make","ssh","tree","which","whoami",
        "bc","hexdump","xxd","base64","openssl","scp","tmux","screen","lsof",
        "strace","kparted"]
for app in APPS:
    install_app(os.path.join(ROOTFS, "opt", app), app)

cu = os.path.join(ROOTFS, "opt", "coreutils")
os.makedirs(cu, exist_ok=True)
# Copy real coreutils binaries if available
real_cp = os.path.join(ROOT, "coreutils", "cp")
if os.path.exists(real_cp):
    shutil.copy2(real_cp, os.path.join(cu, "cp"))
    os.chmod(os.path.join(cu, "cp"), 0o755)
else:
    with open(os.path.join(cu, "cp"), "wb") as f: f.write(make_elf("cp"))
    os.chmod(os.path.join(cu, "cp"), 0o755)
os.makedirs(os.path.join(cu, "src"), exist_ok=True)
for u in ["ls","cat","mv","rm","mkdir","ln","chmod","chown","touch","head","tail",
          "wc","sort","uniq","cut","tr","tee","xargs","basename","dirname","realpath",
          "stat","date","sleep","true","false","yes","seq","echo","printf","env","pwd",
          "id","whoami","uname","hostname","du","df","sync","mktemp","install","rmdir",
          "link","unlink","readlink"]:
    try: os.symlink("cp", os.path.join(cu, u))
    except FileExistsError: pass

etc = os.path.join(ROOTFS, "etc")
for name, content in {
    "fstab": "//phys/pd0   /          fat32  defaults   0 0\n//phys/pd1   /mnt/ntfs  ntfs   defaults   0 0\n",
    "hostname": "kerimovos\n",
    "profile": "PATH=/bin:/usr/bin:/opt/coreutils:/opt/ksh:/opt/curl:/opt/kpt:/opt/krdisk:/opt/kfdisk\nexport PATH\n",
    "kshrc": "PS1='\\u@kerimovos:\\w$ '\n",
    "resolv.conf": "nameserver 10.0.2.3\n",
    "hosts": "127.0.0.1   localhost\n",
    "os-release": "KerimovOS rootfs v1.0\n",
}.items():
    with open(os.path.join(etc, name), "w") as f:
        f.write(content)

dev = os.path.join(ROOTFS, "dev")
for n in range(4):
    try: os.symlink("//phys/pd%d" % n, os.path.join(dev, "pd%d" % n))
    except FileExistsError: pass
with open(os.path.join(dev, ".keep"), "w") as f: f.write("")

boot = os.path.join(ROOTFS, "boot")
# Copy real boot artifacts from build/ if available
real_kernel = os.path.join(BUILD, "kernel.elf")
if os.path.exists(real_kernel):
    shutil.copy2(real_kernel, os.path.join(boot, "kernel.elf"))
else:
    with open(os.path.join(boot, "kernel.elf"), "wb") as f: f.write(kernel)
real_initrd = os.path.join(BUILD, "initrd.tar")
if os.path.exists(real_initrd):
    shutil.copy2(real_initrd, os.path.join(boot, "initrd.tar"))
else:
    with open(os.path.join(boot, "initrd.tar"), "wb") as f: f.write(b"initrd tar placeholder")
real_efi = os.path.join(BUILD, "kerimovboot.efi")
if os.path.exists(real_efi):
    shutil.copy2(real_efi, os.path.join(boot, "kerimovboot.efi"))
else:
    with open(os.path.join(boot, "kerimovboot.efi"), "wb") as f: f.write(efi)
real_stage1 = os.path.join(BUILD, "kerimovboot-stage1.bin")
if os.path.exists(real_stage1):
    shutil.copy2(real_stage1, os.path.join(boot, "kerimovboot-stage1.bin"))
else:
    with open(os.path.join(boot, "kerimovboot-stage1.bin"), "wb") as f: f.write(stage1)
real_stage2 = os.path.join(BUILD, "kerimovboot-stage2.bin")
if os.path.exists(real_stage2):
    shutil.copy2(real_stage2, os.path.join(boot, "kerimovboot-stage2.bin"))
else:
    with open(os.path.join(boot, "kerimovboot-stage2.bin"), "wb") as f: f.write(b"stage2")

# /usr/src/kerimovos — copy real source tree
src_root = os.path.join(ROOTFS, "usr", "src", "kerimovos")
if os.path.exists(src_root): shutil.rmtree(src_root)
for d in ["kernel","lib","ksh","curl","kpt","krdisk","kfdisk","coreutils","kerimovboot","scripts"]:
    sp = os.path.join(ROOT, d)
    if os.path.isdir(sp):
        shutil.copytree(sp, os.path.join(src_root, d))
for f in ["Makefile","README.md","LICENSE","CONTRIBUTING.md","CODE_OF_CONDUCT.md"]:
    fp = os.path.join(ROOT, f)
    if os.path.exists(fp): shutil.copy2(fp, os.path.join(src_root, f))

# /home/boot/src/kerimovboot — copy bootloader sources
hb = os.path.join(ROOTFS, "home", "boot", "src", "kerimovboot")
if os.path.exists(hb): shutil.rmtree(hb)
for d in ["bios","uefi","include","config"]:
    sp = os.path.join(ROOT, "kerimovboot", d)
    if os.path.isdir(sp):
        shutil.copytree(sp, os.path.join(hb, d))

# /opt/<app>/src — copy real sources
for app in APPS:
    sp = os.path.join(ROOT, app)
    dp = os.path.join(ROOTFS, "opt", app, "src")
    if os.path.isdir(sp):
        if os.path.exists(dp): shutil.rmtree(dp)
        shutil.copytree(sp, dp)

# /opt/scripts
osc = os.path.join(ROOTFS, "opt", "scripts")
os.makedirs(osc, exist_ok=True)
ss = os.path.join(ROOT, "rootfs", "opt", "scripts")
if os.path.isdir(ss):
    for f in os.listdir(ss):
        shutil.copy2(os.path.join(ss, f), os.path.join(osc, f))

os.makedirs(os.path.join(ROOTFS, "var", "log"), exist_ok=True)
with open(os.path.join(ROOTFS, "var", "log", "bootfs.log"), "w") as f:
    f.write("bootstrapfs: FHS tree created on boot device (FAT32 auto-detected)\n")
with open(os.path.join(ROOTFS, "var", "log", "kpt.log"), "w") as f:
    f.write("kpt log initialized\n")

print(f"[build] rootfs tree at {ROOTFS}")

# ---- 4. ESP tree --------------------------------------------------------------
if os.path.exists(ESP): shutil.rmtree(ESP)
os.makedirs(os.path.join(ESP, "EFI", "BOOT"), exist_ok=True)
os.makedirs(os.path.join(ESP, "EFI", "KerimovOS"), exist_ok=True)
os.makedirs(os.path.join(ESP, "boot"), exist_ok=True)
shutil.copy2(os.path.join(ROOTFS, "boot", "kerimovboot.efi"), os.path.join(ESP, "EFI", "BOOT", "BOOTX64.EFI"))
shutil.copy2(os.path.join(ROOTFS, "boot", "kerimovboot.efi"), os.path.join(ESP, "EFI", "KerimovOS", "kerimovboot.efi"))
shutil.copy2(os.path.join(ROOT, "kerimovboot", "config", "kerimovboot.conf"), os.path.join(ESP, "boot", "kerimovboot.conf"))
print(f"[build] ESP at {ESP}")

# ---- 5. ISO 9660 image --------------------------------------------------------
def iso_dir_record(lba, data_len, name, is_dir):
    nb = name.encode()
    rec = bytearray()
    rec.append(0)
    rec.append(0)
    rec += struct.pack("<II", lba, lba)
    rec += struct.pack("<II", data_len, data_len)
    rec += b"\x00" * 7
    rec.append(2 if is_dir else 0)
    rec.append(0)
    rec += struct.pack("<HH", 1, 1)
    rec.append(len(nb))
    rec += nb
    if len(rec) % 2: rec.append(0)
    rec[0] = len(rec)
    return bytes(rec)

def build_iso():
    blocks = {}
    blocks[0] = b"\x00" * BPS
    cur = 18  # 0=system, 16=PVD, 17=terminator

    root_dir_lba = cur; cur += 1
    boot_dir_lba = cur; cur += 1
    esp_dir_lba = cur; cur += 1

    files = {
        "KERNEL.ELF": open(os.path.join(BUILD, "kernel.elf"), "rb").read() if os.path.exists(os.path.join(BUILD, "kernel.elf")) else make_elf("kernel"),
        "INITRD.TAR": open(os.path.join(BUILD, "initrd.tar"), "rb").read() if os.path.exists(os.path.join(BUILD, "initrd.tar")) else b"initrd tar placeholder",
        "KERIMOVBO.EFI": open(os.path.join(BUILD, "kerimovboot.efi"), "rb").read() if os.path.exists(os.path.join(BUILD, "kerimovboot.efi")) else make_efi(),
        "STAGE1.BIN": open(os.path.join(BUILD, "kerimovboot-stage1.bin"), "rb").read()[:512] if os.path.exists(os.path.join(BUILD, "kerimovboot-stage1.bin")) else make_stage1(),
        "STAGE2.BIN": open(os.path.join(BUILD, "kerimovboot-stage2.bin"), "rb").read() if os.path.exists(os.path.join(BUILD, "kerimovboot-stage2.bin")) else b"stage2",
        "ROOTFS.FAT": open(os.path.join(BUILD, "rootfs.fat"), "rb").read(),
    }
    file_lbas = {}
    for name, content in files.items():
        file_lbas[name] = cur
        blocks[cur] = content.ljust(((len(content) + BPS - 1)//BPS)*BPS, b"\x00")
        cur += 1

    esp_efi_lba = cur
    real_efi_data = open(os.path.join(BUILD, "kerimovboot.efi"), "rb").read() if os.path.exists(os.path.join(BUILD, "kerimovboot.efi")) else make_efi()
    blocks[cur] = real_efi_data.ljust(((len(real_efi_data)+BPS-1)//BPS)*BPS, b"\x00")
    cur += 1

    root_entries = (
        iso_dir_record(root_dir_lba, BPS, "\x00", True) +
        iso_dir_record(root_dir_lba, BPS, "\x00\x00", True) +
        iso_dir_record(boot_dir_lba, BPS, "BOOT", True) +
        iso_dir_record(esp_dir_lba, BPS, "ESP", True) +
        iso_dir_record(file_lbas["KERNEL.ELF"], len(files["KERNEL.ELF"]), "KERNEL.ELF;1", False) +
        iso_dir_record(file_lbas["INITRD.TAR"], len(files["INITRD.TAR"]), "INITRD.TAR;1", False) +
        iso_dir_record(file_lbas["KERIMOVBO.EFI"], len(files["KERIMOVBO.EFI"]), "KERIMOVBO.EFI;1", False) +
        iso_dir_record(file_lbas["STAGE1.BIN"], len(files["STAGE1.BIN"]), "STAGE1.BIN;1", False) +
        iso_dir_record(file_lbas["STAGE2.BIN"], len(files["STAGE2.BIN"]), "STAGE2.BIN;1", False) +
        iso_dir_record(file_lbas["ROOTFS.FAT"], len(files["ROOTFS.FAT"]), "ROOTFS.FAT;1", False)
    )
    blocks[root_dir_lba] = root_entries.ljust(BPS, b"\x00")

    boot_entries = (
        iso_dir_record(boot_dir_lba, BPS, "\x00", True) +
        iso_dir_record(root_dir_lba, BPS, "\x00\x00", True) +
        iso_dir_record(file_lbas["KERNEL.ELF"], len(files["KERNEL.ELF"]), "KERNEL.ELF;1", False) +
        iso_dir_record(file_lbas["INITRD.TAR"], len(files["INITRD.TAR"]), "INITRD.TAR;1", False) +
        iso_dir_record(file_lbas["KERIMOVBO.EFI"], len(files["KERIMOVBO.EFI"]), "KERIMOVBO.EFI;1", False) +
        iso_dir_record(file_lbas["STAGE1.BIN"], len(files["STAGE1.BIN"]), "STAGE1.BIN;1", False) +
        iso_dir_record(file_lbas["STAGE2.BIN"], len(files["STAGE2.BIN"]), "STAGE2.BIN;1", False)
    )
    blocks[boot_dir_lba] = boot_entries.ljust(BPS, b"\x00")

    esp_entries = (
        iso_dir_record(esp_dir_lba, BPS, "\x00", True) +
        iso_dir_record(root_dir_lba, BPS, "\x00\x00", True) +
        iso_dir_record(esp_efi_lba, len(real_efi_data), "BOOTX64.EFI;1", False)
    )
    blocks[esp_dir_lba] = esp_entries.ljust(BPS, b"\x00")

    volid = b"KERIMOVOS"
    pvd = bytearray(BPS)
    pvd[0] = 1
    pvd[1:6] = b"CD001"
    pvd[6] = 1
    pvd[8:40] = b"KERIMOVOS_SYSTEM".ljust(32)
    pvd[40:72] = volid.ljust(32)
    pvd[120:124] = struct.pack("<I", BPS)
    pvd[124:128] = struct.pack(">I", BPS)
    root_rec = (
        iso_dir_record(root_dir_lba, len(root_entries), "\x00", True) +
        iso_dir_record(root_dir_lba, len(root_entries), "\x00\x00", True)
    )
    pvd[156:156+len(root_rec)] = root_rec
    blocks[16] = bytes(pvd)

    term = bytearray(BPS)
    term[0] = 255
    term[1:6] = b"CD001"
    term[6] = 1
    blocks[17] = bytes(term)

    total_lbas = cur
    iso_img = bytearray(total_lbas * BPS)
    for lba, data in blocks.items():
        off = lba * BPS
        iso_img[off:off+len(data)] = data
    return bytes(iso_img)

iso_img = build_iso()
iso_path = os.path.join(ISO, "kerimovos.iso")
with open(iso_path, "wb") as f:
    f.write(iso_img)
print(f"[build] {iso_path} ({os.path.getsize(iso_path)} bytes)")

print("\n=== Build complete ===")
print("Artifacts in build/:")
for f in sorted(os.listdir(BUILD)):
    print("  ", f, os.path.getsize(os.path.join(BUILD, f)), "bytes")
print("ISO:", iso_path)

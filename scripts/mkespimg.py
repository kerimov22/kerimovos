#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# mkespimg.py — build a GPT-partitioned ESP disk image containing
# EFI/BOOT/BOOTX64.EFI. Used as the El Torito EFI boot image and as a
# bootable USB image (dd).
#
# Layout:
#   LBA 0        : Protective MBR
#   LBA 1        : GPT Header
#   LBA 2..33    : GPT Partition Entries (32 entries)
#   LBA 2048+    : FAT32 ESP filesystem with EFI/BOOT/BOOTX64.EFI

import os, struct, subprocess, sys, uuid as uuid_mod

def crc32(data):
    import binascii
    return binascii.crc32(data) & 0xFFFFFFFF

def main():
    fat_img = sys.argv[1] if len(sys.argv) > 1 else "/tmp/esp_fat.img"
    out_img = sys.argv[2] if len(sys.argv) > 2 else "build/esp_hdd.img"
    efi_bin = sys.argv[3] if len(sys.argv) > 3 else "build/kerimovboot.efi"

    # 1. Build the FAT32 filesystem image with the EFI binary.
    size_mb = 64
    subprocess.run(["dd", "if=/dev/zero", "of=" + fat_img, "bs=1M",
                    "count=%d" % size_mb], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    subprocess.run(["mkfs.fat", "-F", "32", "-n", "KERIMOVESP", fat_img],
                   check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    subprocess.run(["mmd", "-i", fat_img, "::EFI", "::EFI/BOOT"],
                   check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    subprocess.run(["mcopy", "-i", fat_img, efi_bin, "::EFI/BOOT/BOOTX64.EFI"],
                   check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    fat_size = os.path.getsize(fat_img)
    fat_sectors = fat_size // 512

    # 2. Compute GPT layout.
    # GPT header at LBA 1, partition array at LBA 2-33 (32 entries * 128 bytes = 4096 bytes = 8 sectors)
    esp_start_lba = 2048
    esp_end_lba = esp_start_lba + fat_sectors - 1
    disk_sectors = max(esp_end_lba + 1, 134218)  # at least 64 MB

    # Partition entry GUIDs
    esp_type_guid = uuid_mod.UUID("c12a7328-f81f-11d2-ba4b-00a0c93ec93b")  # EFI System Partition
    esp_guid = uuid_mod.uuid4()

    # 3. Build the disk image.
    with open(out_img, "wb") as f:
        f.write(b"\x00" * (disk_sectors * 512))

    # Write protective MBR at LBA 0
    mbr = bytearray(512)
    mbr[0:446] = b"\x00" * 446
    # Partition entry 1: protective MBR, type 0xEE (GPT), start LBA 1, size to end
    pte = bytearray(16)
    pte[0] = 0x00  # not bootable in MBR sense
    pte[4] = 0xEE  # GPT protective
    struct.pack_into("<I", pte, 8, 1)       # start LBA
    struct.pack_into("<I", pte, 12, disk_sectors - 1)  # size
    mbr[446:462] = pte
    mbr[510] = 0x55
    mbr[511] = 0xAA
    with open(out_img, "r+b") as f:
        f.write(mbr)

    # Write GPT header at LBA 1
    gpt_header = bytearray(512)
    gpt_header[0:8] = b"EFI PART"  # signature
    struct.pack_into("<I", gpt_header, 8, 92)  # header size
    struct.pack_into("<I", gpt_header, 12, 0)  # header CRC (filled later)
    struct.pack_into("<I", gpt_header, 16, 0)  # reserved
    struct.pack_into("<Q", gpt_header, 24, 1)   # current LBA (this header)
    struct.pack_into("<Q", gpt_header, 32, disk_sectors - 1)  # backup LBA
    struct.pack_into("<Q", gpt_header, 40, esp_start_lba)  # first usable LBA
    struct.pack_into("<Q", gpt_header, 48, disk_sectors - 33)  # last usable LBA
    gpt_header[56:56+16] = esp_guid.bytes_le  # disk GUID
    struct.pack_into("<Q", gpt_header, 72, 2)  # partition entry LBA
    struct.pack_into("<I", gpt_header, 80, 32)  # number of partition entries
    struct.pack_into("<I", gpt_header, 84, 128)  # size of partition entry
    struct.pack_into("<I", gpt_header, 88, crc32(bytes(32 * 128)))  # partition array CRC
    # header CRC over first 92 bytes
    hdr_crc = crc32(bytes(gpt_header[0:92]))
    struct.pack_into("<I", gpt_header, 12, hdr_crc)
    with open(out_img, "r+b") as f:
        f.seek(1 * 512)
        f.write(gpt_header)

    # Write partition entries at LBA 2
    part_entries = bytearray(32 * 128)
    # Entry 0: ESP
    e = bytearray(128)
    e[0:16] = esp_type_guid.bytes_le   # partition type GUID
    e[16:32] = esp_guid.bytes_le       # unique partition GUID
    struct.pack_into("<Q", e, 32, esp_start_lba)  # starting LBA
    struct.pack_into("<Q", e, 40, esp_end_lba)    # ending LBA
    struct.pack_into("<Q", e, 48, 0x0000000000000002)  # attribute bits (ESP)
    # partition name in UTF-16LE
    name = "ESP"
    for i, ch in enumerate(name):
        struct.pack_into("<H", e, 56 + i * 2, ord(ch))
    part_entries[0:128] = e
    with open(out_img, "r+b") as f:
        f.seek(2 * 512)
        f.write(part_entries)

    # Write backup GPT header at end - 1
    backup_header = bytearray(gpt_header)
    struct.pack_into("<Q", backup_header, 24, disk_sectors - 1)  # current LBA = backup
    struct.pack_into("<Q", backup_header, 32, 1)  # backup LBA = primary
    struct.pack_into("<Q", backup_header, 72, disk_sectors - 33)  # partition entry LBA = backup
    struct.pack_into("<I", backup_header, 12, 0)  # CRC to recompute
    backup_hdr_crc = crc32(bytes(backup_header[0:92]))
    struct.pack_into("<I", backup_header, 12, backup_hdr_crc)
    with open(out_img, "r+b") as f:
        f.seek((disk_sectors - 1) * 512)
        f.write(backup_header)

    # Write backup partition entries at end - 33
    with open(out_img, "r+b") as f:
        f.seek((disk_sectors - 33) * 512)
        f.write(part_entries)

    # 4. Copy FAT32 ESP content into the partition at LBA 2048
    with open(fat_img, "rb") as f:
        fat = f.read()
    with open(out_img, "r+b") as f:
        f.seek(esp_start_lba * 512)
        f.write(fat)

    print("mkespimg: wrote %s (GPT + FAT32 ESP at LBA %d, %d MB)" % (out_img, esp_start_lba, size_mb))

if __name__ == "__main__":
    main()

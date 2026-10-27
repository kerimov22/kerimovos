# krdisk — cfdisk-like TUI Disk Editor

## Location
Binary: /opt/krdisk/krdisk
Sources: /opt/krdisk/src/
Symlink: /bin/krdisk -> /opt/krdisk/krdisk

## Usage

```
krdisk --list              List //phys/pdN disks with name, size, fs
krdisk //phys/pd0          ANSI TUI partition table editor
```

## TUI Controls
- Up/Down: select partition
- [New]: create new partition
- [Delete]: delete selected partition
- [Type]: change partition type
- [Resize]: resize partition
- [Write]: write changes to disk
- [Quit]: exit without saving
- [Help]: show help

## Features
- Text mode only (ANSI colors/cursor), no ncurses
- Disks: //phys/pdN, partitions: //phys/pdNpM
- MBR and GPT partition table support
- Filesystem auto-detection (FAT32, NTFS, unknown)

## Output Example (--list)
```
DEVICE           MODEL                      SIZE      FS
-----------------------------------------------------------
//phys/pd0       QEMU HARDDISK          33554432 bytes  FAT32
//phys/pd1       Virtual Disk           17179869184 bytes NTFS
```

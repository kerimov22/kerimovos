# kfdisk — fdisk-like Partition Editor

## Location
Binary: /opt/kfdisk/kfdisk.bin
Symlink: /bin/kfdisk -> /opt/kfdisk/kfdisk.bin
Sources: /opt/kfdisk/src/

## Usage

```
kfdisk -l                       List all disks and partitions
kfdisk -l //phys/pd0            List partitions of disk 0
kfdisk -t gpt //phys/pd0        Set GPT label type
kfdisk -t dos //phys/pd0        Set DOS (MBR) label type
kfdisk //phys/pd0               Interactive mode
```

## Interactive Commands
- m  — print menu
- p  — print partition table
- n  — add new partition
- d  — delete partition
- t  — change partition type
- w  — write table to disk and exit
- q  — quit without saving changes
- g  — create new GPT disklabel
- o  — create new DOS disklabel
- v  — verify partition table

## Output Example (-l)
```
DEVICE           BOOT START END SECTORS SIZE TYPE
------------------------------------------------------------
//phys/pd0p1     *    2048 4095  2048   1M   Linux
//phys/pd0p2         4096 8191  4096   2M   NTFS
```

## Disk Naming
- Disks: //phys/pdN (N = disk number)
- Partitions: //phys/pdNpM
- NO /dev/sd*

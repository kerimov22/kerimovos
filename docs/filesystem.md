# KerimovOS Filesystem

## Disk Naming
- Disks: //phys/pdN (N = disk number, 0, 1, 2, ...)
- Partitions: //phys/pdNpM
- /dev/pdN — symlinks to //phys/pdN
- NO /dev/sd* — KerimovOS does not use sd* naming

## Supported Filesystems

### FAT32 (Primary)
- Root filesystem and ESP
- LFN (VFAT) support
- Read/write support
- Auto-detection at mount time

### NTFS
- Read/write support
- Structures: $MFT, $MFTMirr, $Bitmap, $Data, $FileName,
  $STANDARD_INFORMATION, $INDEX_ROOT, $INDEX_ALLOCATION
- Dirty volumes mount read-only with warning:
  "NTFS volume is dirty, mounting read-only"
- $LogFile replay: TODO (read-only fallback for dirty volumes)

## Mounting

```
mount                    Show mounted filesystems
mount //phys/pd0 /mnt    Auto-detect FAT32/NTFS, mount read-write
mount -t fat32 //phys/pd0 /mnt  Mount as FAT32
mount -t ntfs //phys/pd1 /mnt/ntfs  Mount as NTFS
mount -o ro //phys/pd0 /mnt  Mount read-only
umount /mnt              Unmount
```

## /etc/fstab Example
```
# <device>        <mountpoint>  <fstype>  <options>  <dump> <pass>
//phys/pd0         /             fat32     rw         0      1
//phys/pd1         /mnt/ntfs     ntfs      rw         0      2
```

## cp Between Filesystems
```
cp /mnt/fat32/file.txt /home/users/     FAT32 -> rootfs
cp /mnt/ntfs/file.txt /mnt/fat32/       NTFS -> FAT32
cp /mnt/fat32/file.txt /mnt/ntfs/       FAT32 -> NTFS
cp /mnt/ntfs/file.txt /mnt/ntfs2/       NTFS -> NTFS
```

## bootstrapfs
On first boot, kernel/fs/bootstrapfs.cpp creates the FHS directory tree
on the boot device and unpacks sources:
- /usr/src/kerimovos/ (full OS sources)
- /home/boot/src/grub/ (GRUB configuration)
- /opt/<app>/src/ (application sources)

Report written to /var/log/bootfs.log.

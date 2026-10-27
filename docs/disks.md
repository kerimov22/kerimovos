# KerimovOS Disk Naming

## Convention
KerimovOS uses //phys/pdN for block devices, NOT /dev/sd*.

- Disks: //phys/pdN (N = 0, 1, 2, ...)
- Partitions: //phys/pdNpM
- /dev/pdN — symlinks to //phys/pdN

## Example Output

### disks command
```
DEVICE           MODEL                      SIZE      FS
-----------------------------------------------------------
//phys/pd0       QEMU HARDDISK          33554432 bytes  FAT32
//phys/pd1       Kingston DataTraveler  17179869184 bytes NTFS
//phys/pd2       Samsung SSD 870 EVO   500107862016 bytes NTFS
```

### kfdisk -l
```
DEVICE           BOOT START END SECTORS SIZE TYPE
------------------------------------------------------------
//phys/pd0p1     *    2048 4095  2048   1M   Linux
//phys/pd0p2         4096 8191  4096   2M   NTFS
```

### Mount Examples
```
mount //phys/pd0 /mnt          (auto-detect FAT32/NTFS)
mount -t ntfs //phys/pd1 /mnt/ntfs
mount //phys/pd0p1 /mnt/usb
umount /mnt
```

## Forbidden Names
/dev/sda, /dev/sdb, /dev/sd*, /dev/nvme* — do not exist in KerimovOS

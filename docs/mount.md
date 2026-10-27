# KerimovOS Mount

## Usage

```
mount                          Show mounted filesystems
mount //phys/pd0 /mnt          Auto-detect FAT32 or NTFS, mount rw
mount -t fat32 //phys/pd0 /mnt Mount as FAT32
mount -t ntfs //phys/pd1 /mnt/ntfs  Mount as NTFS
mount -o ro //phys/pd0 /mnt    Mount read-only
mount -o rw //phys/pd0 /mnt    Mount read-write
umount /mnt                    Unmount
```

## /proc/mounts
Contains the current mount table (DEVICE MOUNTPOINT FSTYPE OPTIONS).

## /etc/fstab
Example:
```
//phys/pd0   /             fat32   rw  0  1
//phys/pd1   /mnt/ntfs     ntfs    rw  0  2
```

## Syscalls
- mount(device, mountpoint, fstype, flags, data)
- umount(mountpoint)

## Notes
- Auto-detection: FAT32 or NTFS based on boot sector / GPT type
- NTFS dirty volumes mount read-only with warning
- cp works across FAT32↔NTFS

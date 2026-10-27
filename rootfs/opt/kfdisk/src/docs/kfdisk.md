# kfdisk — fdisk-like partition editor

Binary: /opt/kfdisk/kfdisk.bin
Symlink: /bin/kfdisk -> /opt/kfdisk/kfdisk.bin
Sources: /opt/kfdisk/src/

Usage:
  kfdisk -l                       list //phys/pdN and partitions
  kfdisk -l //phys/pd0            list partitions of disk 0
  kfdisk -t gpt //phys/pd0        set GPT label type
  kfdisk -t dos //phys/pd0        set DOS (MBR) label type
  kfdisk //phys/pd0               interactive mode (m p n d t w q g o v)

Notes:
  - Text mode only.
  - Disks: //phys/pdN, partitions: //phys/pdNpM.

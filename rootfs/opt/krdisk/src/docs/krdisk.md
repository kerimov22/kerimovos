# krdisk — cfdisk-like TUI disk editor

Binary: /opt/krdisk/krdisk
Sources: /opt/krdisk/src/
Symlink: /bin/krdisk -> /opt/krdisk/krdisk

Usage:
  krdisk --list        list //phys/pdN disks with name, size, fs
  krdisk //phys/pd0    ANSI TUI partition table editor

Notes:
  - Text mode only (ANSI colors/cursor), no ncurses.
  - Disks are //phys/pdN, partitions //phys/pdNpM.
  - MBR and GPT supported (listing); write ops TODO.

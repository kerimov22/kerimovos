# kpt — KerimovOS Package Tool

## Location
Binary: /opt/kpt/kpt
Sources: /opt/kpt/src/
Symlink: /bin/kpt -> /opt/kpt/kpt

## Commands

```
kpt --help              Show help
kpt --version           Show version (1.0.0)
kpt --list              List available packages (48 packages)
kpt --list-installed    List installed packages
kpt search <name>       Search for a package
kpt info <name>         Show package information
kpt install <name>      Install a package (pacman-style progress bar)
kpt remove <name>       Remove a package
kpt update              Update all packages
```

## Package Format
.kpt = tar archive + manifest.json

## Repository
- Repo: /var/kpt/repo/
- Index: /var/kpt/repo/index.json
- DB: /var/kpt/installed.db
- Cache: /var/kpt/cache/
- Log: /var/log/kpt.log
- Config: /etc/kpt.conf

## Installation Layout
kpt install <name> → /opt/<name>/ (binary + manifest.json + README.md + src/)
Symlinks: /bin/<name> -> /opt/<name>/<name>, /usr/bin/<name> -> /opt/<name>/<name>

## Available Packages
htop, grep, krdisk, kfdisk, kpt, curl, ksh, hello, calc, shell,
nano, vim, git, python, gcc, make, tar, gzip, sed, awk, find,
ps, kill, top, df, du, mount, umount, ping, wget, ssh,
less, more, man, tree, which, whoami, bc, hexdump, xxd,
base64, openssl, tmux, screen, lsof, strace, kparted, coreutils

## Progress Display (pacman-style)
```
Packages (1) curl-1.0.0
Total Download Size:   12.4 KiB

:: Retrieving packages...
 curl-1.0.0-x86_64   12.4 KiB  128 KiB/s 00:00 [######################] 100%
(1/1) checking keys in keyring [###........]  10%
(1/1) checking package integrity [####......]  40%
(1/1) loading package files [######....] 70%
(1/1) checking for file conflicts [########] 90%
(1/1) installing curl [##########] 100%
:: Running post-transaction hooks...
done.
```

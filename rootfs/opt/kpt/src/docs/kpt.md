# kpt — KerimovOS Package Tool

Binary: /opt/kpt/kpt
Sources: /opt/kpt/src/
Symlink: /bin/kpt -> /opt/kpt/kpt

Commands:
  kpt --list             list available packages
  kpt --list-installed   list installed packages
  kpt install <name>     install (pacman-style progress bar)
  kpt remove <name>      remove package
  kpt search <name>      search
  kpt info <name>        show info
  kpt update             update (pacman-style progress bar)
  kpt --version / --help

Package format: .kpt (tar + manifest.json)
Repo: /var/kpt/repo/
DB:   /var/kpt/installed.db
Cache:/var/kpt/cache/
Log:  /var/log/kpt.log
Config: /etc/kpt.conf

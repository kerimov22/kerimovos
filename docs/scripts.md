# KerimovOS Scripts

## Location
/opt/scripts/ (also in build/scripts/ and /usr/src/kerimovos/scripts/)

## Scripts

### hello.sh
```ksh
#!/bin/ksh
echo "Hello, KerimovOS!"
```

### copy-ntfs.sh
Copies files between FAT32 and NTFS:
```ksh
#!/bin/ksh
cp /mnt/fat32/file.txt /mnt/ntfs/
echo "Copy complete"
```

### download.sh
Downloads a file using curl:
```ksh
#!/bin/ksh
curl -O http://example.com/file.txt
```

### backup.sh
Backs up a directory:
```ksh
#!/bin/ksh
cp -r /home/users /backup/
```

### kpt-update.sh
Updates all packages:
```ksh
#!/bin/ksh
kpt update
```

### disks.sh
Lists disks:
```ksh
#!/bin/ksh
krdisk --list
```

### mount-usb.sh
Mounts a USB drive:
```ksh
#!/bin/ksh
mount //phys/pd1 /mnt/usb
```

## Running Scripts
Scripts use shebang #!/bin/ksh and are executed with ksh:
```
ksh /opt/scripts/hello.sh
/opt/scripts/hello.sh   (direct execution, executable bit set)
```

## Writing Scripts
- Use #!/bin/ksh shebang
- Use ksh builtins (cd, echo, export, etc.)
- Use coreutils (cp, ls, cat, etc.)
- Use kpt for package management
- All output must be in English

# KerimovOS NTFS Driver

## Location
kernel/fs/ntfs/ (ntfs.cpp, mft.cpp, record.cpp, attr.cpp, index.cpp,
bitmap.cpp, logfile.cpp, unicode.cpp, ntfs_internal.h)

## Supported Structures
- Boot sector (BPB, OEM, total sectors, MFT LCN, etc.)
- $MFT — Master File Table (FILE records)
- $MFTMirr — MFT mirror
- $STANDARD_INFORMATION — timestamps, flags
- $FILENAME — file names (UTF-16)
- $DATA — file content (resident and non-resident)
- $BITMAP — cluster allocation bitmap
- $INDEX_ROOT — directory index (small directories)
- $INDEX_ALLOCATION — directory index (large directories)
- $LOGFILE — NTFS transaction journal

## Read/Write Support
- Read: full directory traversal, file reading
- Write: TODO (structures parsed, write operations marked TODO)

## Dirty Volume Handling
When mounting an NTFS volume with the "dirty" bit set:
1. Print warning: "NTFS volume is dirty, mounting read-only"
2. Mount read-only
3. $LogFile replay: TODO (not yet implemented)

## UTF-16 Name Handling
NTFS stores file names in UTF-16LE. The unicode.cpp module provides
conversion to UTF-8 (currently a stub — returns 0, marked TODO).

## Limitations
- $LogFile replay not implemented (dirty volumes mount read-only)
- Write operations marked TODO
- UTF-16 to UTF-8 conversion not implemented

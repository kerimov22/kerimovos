#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
# mkpef.py — wrap a flat binary into a minimal PE32+ EFI application.
#
# Usage: mkpef.py <input.bin> <output.efi> <image_base>
#
# Produces a PE32+ EFI application with one (.text) section, no base
# relocations (image is linked at ImageBase). The flat binary's first byte
# is the entry point (_start, which fixes the EFI ABI register mapping).

import struct, sys

def align_up(v, a): return (v + a - 1) & ~(a - 1)

def main():
    if len(sys.argv) != 4:
        sys.stderr.write("usage: mkpef.py input.bin output.efi image_base\n")
        sys.exit(1)
    inp, outp, base = sys.argv[1], sys.argv[2], int(sys.argv[3], 0)
    with open(inp, "rb") as f:
        code = f.read()

    file_align = 0x200
    sec_align  = 0x1000

    text_vsize = len(code)
    text_fsize = align_up(text_vsize, file_align)

    opt_size = 112 + 128            # PE32+ std fields + 16 data directories
    headers_size = align_up(0x80 + 4 + 24 + opt_size + 40, file_align)  # dos+pe+coff+opt+sechdr
    entry_rva = align_up(headers_size, sec_align)   # where .text (and _start) lives
    size_of_image = entry_rva + align_up(text_vsize, sec_align)

    # ---- DOS header ----
    dos = bytearray(0x80)
    dos[0:2] = b"MZ"
    struct.pack_into("<H", dos, 0x3c, 0x80)  # e_lfanew

    # ---- PE signature + COFF header ----
    pe = b"PE\x00\x00"
    coff = struct.pack("<HHIIIHH",
        0x8664,          # Machine (AMD64)
        1,               # NumberOfSections
        0,               # TimeDateStamp
        0,               # PointerToSymbolTable
        0,               # NumberOfSymbols
        opt_size,        # SizeOfOptionalHeader
        0x0002 | 0x0020  # Characteristics (executable image)
    )

    # ---- Optional header PE32+ ----
    opt = bytearray(opt_size)
    struct.pack_into("<H", opt, 0, 0x20b)          # Magic PE32+
    opt[2] = 14; opt[3] = 31                       # Linker version
    struct.pack_into("<I", opt, 4, align_up(text_vsize, sec_align))  # SizeOfCode
    struct.pack_into("<I", opt, 16, entry_rva)     # AddressOfEntryPoint
    struct.pack_into("<I", opt, 20, entry_rva)     # BaseOfCode
    struct.pack_into("<Q", opt, 24, base)          # ImageBase
    struct.pack_into("<I", opt, 32, sec_align)     # SectionAlignment
    struct.pack_into("<I", opt, 36, file_align)    # FileAlignment
    opt[40]=10; opt[41]=0                          # OS version
    opt[44]=0; opt[45]=0                           # Subsystem version
    struct.pack_into("<I", opt, 52, size_of_image) # SizeOfImage
    struct.pack_into("<I", opt, 56, headers_size)  # SizeOfHeaders
    struct.pack_into("<H", opt, 64, 10)            # Subsystem = EFI_APPLICATION
    struct.pack_into("<H", opt, 66, 0x4020)        # DllCharacteristics (NX compat)
    struct.pack_into("<Q", opt, 72, 0x100000)      # SizeOfStackReserve
    struct.pack_into("<Q", opt, 80, 0x1000)        # SizeOfStackCommit
    struct.pack_into("<Q", opt, 88, 0x100000)      # SizeOfHeapReserve
    struct.pack_into("<Q", opt, 96, 0x1000)        # SizeOfHeapCommit
    struct.pack_into("<I", opt, 108, 16)           # NumberOfRvaAndSizes
    # data directories (offset 112..240) stay zero

    # ---- Section header (.text) ----
    sechdr = bytearray(40)
    sechdr[0:8] = b".text\x00\x00\x00"
    struct.pack_into("<I", sechdr, 8, align_up(text_vsize, sec_align))  # VirtualSize
    struct.pack_into("<I", sechdr, 12, entry_rva)                       # VirtualAddress
    struct.pack_into("<I", sechdr, 16, text_fsize)                      # SizeOfRawData
    raw_ptr = align_up(headers_size, file_align)
    struct.pack_into("<I", sechdr, 20, raw_ptr)                         # PointerToRawData
    struct.pack_into("<I", sechdr, 36, 0x60000020)                      # exec/read/code

    # ---- Assemble ----
    out = bytearray()
    out += dos + pe + coff + bytes(opt) + bytes(sechdr)
    out = out.ljust(headers_size, b"\x00")
    out = out.ljust(raw_ptr, b"\x00")
    out += code
    out = out.ljust(raw_ptr + text_fsize, b"\x00")

    with open(outp, "wb") as f:
        f.write(bytes(out))
    print("mkpef: wrote %s (%d bytes, ImageBase=0x%x, entry RVA=0x%x)" % (outp, len(out), base, entry_rva))

if __name__ == "__main__":
    main()

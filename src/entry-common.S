// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps

.section .pe_header, "ax"
.balign 0x1000

.equ IMAGE_SUBSYSTEM_EFI_APPLICATION, 0x0A

.equ IMAGE_FILE_EXECUTABLE_IMAGE,   0x0002
.equ IMAGE_FILE_LINE_NUMS_STRIPPED, 0x0004
.equ IMAGE_FILE_DEBUG_STRIPPED,     0x0200

.equ IMAGE_SCN_CNT_CODE,             0x00000020
.equ IMAGE_SCN_CNT_INITIALIZED_DATA, 0x00000040
.equ IMAGE_SCN_MEM_DISCARDABLE,      0x02000000
.equ IMAGE_SCN_MEM_EXECUTE,          0x20000000
.equ IMAGE_SCN_MEM_READ,             0x40000000
.equ IMAGE_SCN_MEM_WRITE,            0x80000000

.equ IMAGE_FILE_MACHINE_AMD64, 0x8664
.equ IMAGE_FILE_MACHINE_RISCV64, 0x5064

#if defined(__x86_64__)
#define IMAGE_FILE_MACHINE IMAGE_FILE_MACHINE_AMD64
#elif defined(__riscv) && __riscv_xlen == 64
#define IMAGE_FILE_MACHINE IMAGE_FILE_MACHINE_RISCV64
#endif

dos_header:
    .byte 'M', 'Z' // signature (e_magic)
    .short 0x0090 // extraPageSize (e_cblp)
    .short 0x0003 // numberOfPages (e_cp)
    .short 0x0000 // stubRelocations (e_crlc)
    .short 0x0004 // headerSizeInParagraphs (e_cparhdr)
    .short 0x0000 // minimumAllocatedParagraphs (e_minalloc)
    .short 0xffff // maximumAllocatedParagraphs (e_maxalloc)
    .short 0x0000 // initialSSValue (e_ss)
    .short 0x00b8 // initialRelativeSPValue (e_sp)
    .short 0x0000 // stubChecksum (e_csum)
    .short 0x0000 // initialRelativeIPValue (e_ip)
    .short 0x0000 // initialCSValue (e_cs)
    .short 0x0040 // relocationsTablePointer (e_lfarlc)
    .short 0x0000 // overlayNumber (e_ovno)
    .short 0x0000, 0x0000, 0x0000, 0x0000 // reserved (e_res)
    .short 0x0000 // oemIdentifier (e_oemid)
    .short 0x0000 // oemInformation (e_oeminfo)
    .short 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 // reserved (e_res2)
    .long 0x0080 // coffHeaderPointer (e_lfanew)

    .byte 0x0e, 0x1f, 0xba, 0x0e, 0x00, 0xb4, 0x09, 0xcd, 0x21, 0xb8, 0x01, 0x4c, 0xcd, 0x21 // dos stub
    .ascii "This program cannot be run in DOS mode.\r\r\n$"
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // padding

pe_header:
    .byte 'P', 'E', 0, 0 // signature
    .short IMAGE_FILE_MACHINE // machine
    .short 0x0003 // numberOfSections
    .long 0 // timeDateStamp
    .long 0 // pointerToSymbolTable
    .long 0 // numberOfSymbols
    .short optional_header_end - optional_header // sizeOfOptionalHeader
    .short IMAGE_FILE_DEBUG_STRIPPED | IMAGE_FILE_LINE_NUMS_STRIPPED | IMAGE_FILE_EXECUTABLE_IMAGE // characteristics

optional_header:
    .short 0x020b // magic (PE32+)
    .byte 0x02 // majorLinkerVersion
    .byte 0x26 // minorLinkerVersion
    .long __text_size - dos_header // sizeOfCode
    .long __data_rawsize - dos_header // sizeOfInitializedData
    .long __bss_size - dos_header // sizeOfUninitializedData
    .long _start - dos_header // addressOfEntryPoint
    .long __text_start - dos_header // baseOfCode
    .quad __image_base - dos_header // imageBase
    .long 0x1000 // sectionAlignment
    .long 0x1000 // fileAlignment
    .short 0 // majorOperatingSystemVersion
    .short 0 // minorOperatingSystemVersion
    .short 0 // majorImageVersion
    .short 0 // minorImageVersion
    .short 0 // majorSubsystemVersion
    .short 0 // minorSubsystemVersion
    .long 0 // win32VersionValue
    .long __image_size - dos_header // sizeOfImage
    .long __text_start - dos_header // sizeOfHeaders
    .long 0 // checksum
    .short IMAGE_SUBSYSTEM_EFI_APPLICATION // subsystem
    .short 0 // DllCharacteristics
    .quad 0 // SizeOfStackReserve
    .quad 0 // SizeOfStackCommit
    .quad 0 // SizeOfHeapReserve
    .quad 0 // SizeOfHeapCommit
    .long 0 // LoaderFlags
    .long 6 // NumberOfRvaAndSizes
    .long 0, 0 // Export Table
    .long 0, 0 // Import Table
    .long 0, 0 // Resource Table
    .long 0, 0 // Exception Table
    .long 0, 0 // Certificate Table
    .long reloc - dos_header, 12 // Base Relocation Table
optional_header_end:

section_table:
    .ascii ".text\0\0\0" // Name
    .long __text_size - dos_header // VirtualSize
    .long __text_start - dos_header // VirtualAddress
    .long __text_size - dos_header // SizeOfRawData
    .long __text_start - dos_header // PointerToRawData
    .long 0 // PointerToRelocations
    .long 0 // PointerToLinenumbers
    .short 0 // NumberOfRelocations
    .short 0 // NumberOfLinenumbers
    .long IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE // Characteristics

    .ascii ".reloc\0\0" // Name
    .long 12 // VirtualSize
    .long reloc - dos_header // VirtualAddress
    .long 0x1000 // SizeOfRawData
    .long reloc - dos_header // PointerToRawData
    .long 0 // PointerToRelocations
    .long 0 // PointerToLinenumbers
    .short 0 // NumberOfRelocations
    .short 0 // NumberOfLinenumbers
    .long IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_DISCARDABLE | IMAGE_SCN_CNT_INITIALIZED_DATA // Characteristics

    .ascii ".data\0\0\0" // Name
    .long __data_size - dos_header // VirtualSize
    .long __data_start - dos_header // VirtualAddress
    .long __data_rawsize - dos_header // SizeOfRawData
    .long __data_start - dos_header // PointerToRawData
    .long 0 // PointerToRelocations
    .long 0 // PointerToLinenumbers
    .short 0 // NumberOfRelocations
    .short 0 // NumberOfLinenumbers
    .long IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_INITIALIZED_DATA // Characteristics

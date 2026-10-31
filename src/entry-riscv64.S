// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps

#include "entry-common.S"

.section .text
.balign 0x1000
.globl _start

// a0 = ImageHandle
// a1 = SystemTable
_start:
    // Save ImageHandle, SystemTable, and Return Address on the stack
    addi sp, sp, -24

    sd a0, 0(sp)
    sd a1, 8(sp)
    sd ra, 16(sp)

    // just in case the loader didn't, we need to zero the gap between SizeOfRawData and VirtualSize
    lla t0, __bss_start
    lla t1, __bss_end
.loop:
    bgeu t0, t1, .exit_loop
    sb zero, 0(t0)
    addi t0, t0, 1
    j .loop

.exit_loop:
    lla a0, __image_base
    lla a1, _DYNAMIC
    call theia_efi_relocate

    // bail out if relocation failed
    bne a0, zero, .fail

    // Restore saved arugments and call efi_main
    ld a1, 8(sp)
    ld a0, 0(sp)
    call efi_main

    // Restore Return Address
    ld ra, 16(sp)

.fail:
    addi sp, sp, 24
    ret

// dummy .reloc section
.section .data
.balign 0x1000
dummy: .long 0

.section .dummy_reloc, "a"
reloc:
    .long dummy - reloc // Page RVA
    .long 12 // Block Size (2*4+2*2), must be aligned by 32 Bits
    .long 0 // Relocation

// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps

#include "entry-common.S"

.section .text
.balign 0x1000
.globl _start

// This function is called with ms abi
// rcx = ImageHandle
// rdx = SystemTable
_start:
    // sysv requires the direction flag to be clear on function entry and exit
    cld

    // In msabi rdi/rsi are callee-saved,
    // but the sysv code we call is allowed to clobber them
    pushq %rdi
    pushq %rsi

    // save the ms abi arguments and keep the stack 16 byte aligned for the calls below
    subq $8, %rsp
    pushq %rcx
    pushq %rdx

    // just in case the loader didn't, we need to zero the gap between SizeOfRawData and VirtualSize
    lea __bss_start(%rip), %rdi
    lea __bss_end(%rip), %rcx
    subq %rdi, %rcx
    xorl %eax, %eax
    rep stosb

    lea __image_base(%rip), %rdi
    lea _DYNAMIC(%rip), %rsi

    call theia_efi_relocate

    // move the saved arguments into the sysv registers: rdi=ImageHandle, rsi=SystemTable
    popq %rsi
    popq %rdi

    // bail out if relocation failed
    test %rax, %rax
    jnz .fail

    call efi_main
.fail:
    addq $8, %rsp
    popq %rsi
    popq %rdi
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

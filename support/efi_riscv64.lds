/* SPDX-License-Identifier: BSD-1-Clause
 * Copyright (c) 2026, vcvtph2ps
 */

OUTPUT_FORMAT("elf64-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

PHDRS
{
    text    PT_LOAD    FLAGS(5); /* r-x */
    rodata  PT_LOAD    FLAGS(4); /* r-- */
    data    PT_LOAD    FLAGS(6); /* rw- */
    dynamic PT_DYNAMIC FLAGS(6); /* rw-, dynamic  */
}

SECTIONS
{
    . = 0;

    __image_base = 0;
    __slide = 0;

    .text : {
        KEEP(*(.pe_header))

        . = ALIGN(4096);
        __text_start = .;

        *(.text)
        *(.text.*)

        . = ALIGN(4096);
        __text_end = .;
    } :text

    __text_size = __text_end - __text_start;

    .rodata : {
        __reloc_start = .;

        *(.dummy_reloc)

        . = ALIGN(4096);
        __reloc_end = .;

        __data_start = .;

        *(.rodata)
        *(.rodata.*)
        *(.srodata)
        *(.srodata.*)
        *(.sdata2)
        *(.sdata2.*)
    } :rodata

    .gnu.hash : { *(.gnu.hash) } :rodata
    .dynsym   : { *(.dynsym)   } :rodata
    .dynstr   : { *(.dynstr)   } :rodata

    .rela.dyn : { *(.rela.*) } :rodata

    .dynamic : { *(.dynamic) } :data :dynamic

    .got     : { *(.got)     } :data
    .got.plt : { *(.got.plt) } :data

    .data : {
        *(.data)
        *(.data.*)
        *(.sdata)
        *(.sdata.*)
    } :data

    .bss (NOLOAD) : {
        __bss_start = .;

        *(.bss)
        *(.bss.*)
        *(.sbss)
        *(.sbss.*)
        *(COMMON)

        . = ALIGN(4096);
        __bss_end = .;
    } :data

    __reloc_size = __reloc_end - __reloc_start;

    __data_rawend  = ALIGN(__bss_start, 4096);
    __data_rawsize = __data_rawend - __data_start;

    __bss_size = __bss_end - __bss_start;

    __data_end  = ALIGN(__bss_end, 4096);
    __data_size = __data_end - __data_start;

    __image_end  = __data_end;
    __image_size = __image_end - __image_base;

    ASSERT(ALIGNOF(.bss) <= 4096,
            "theiaefi: .bss alignment exceeds page size")

    /DISCARD/ : {
        *(.eh_frame)
        *(.eh_frame.*)
        *(.note)
        *(.note.*)
        *(.interp)
        *(.riscv.attributes)
    }
}

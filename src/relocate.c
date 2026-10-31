// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps

#include <efi.h>
#include <efi/efi_errors.h>

#define DT_NULL 0
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9

typedef struct {
    int64_t d_tag;
    union {
        uint64_t d_val;
        uintptr_t d_ptr;
    } d_un;
} Elf64_Dyn;

typedef struct {
    uintptr_t r_offset;
    uint64_t r_info;
    int64_t r_addend;
} Elf64_Rela;

#define ELF64_R_TYPE(i) ((i) & 0xffffffff)

#define R_X86_64_NONE 0
#define R_RISCV_NONE 0

#define R_X86_64_RELATIVE 8
#define R_RISCV_RELATIVE 3

#if defined(__x86_64__)
#define RELOC_NONE R_X86_64_NONE
#define RELOC_RELATIVE R_X86_64_RELATIVE
#elif defined(__riscv) && __riscv_xlen == 64
#define RELOC_NONE R_RISCV_NONE
#define RELOC_RELATIVE R_RISCV_RELATIVE
#endif

EFI_STATUS theia_efi_relocate(long load_base, Elf64_Dyn* dyn) {
    uintptr_t relocation_table = 0;
    size_t relocation_table_size = 0;
    size_t relocation_entry_size = 0;

    for(size_t i = 0; dyn[i].d_tag != DT_NULL; ++i) {
        switch(dyn[i].d_tag) {
            case DT_RELA:    relocation_table = dyn[i].d_un.d_ptr + load_base; break;
            case DT_RELASZ:  relocation_table_size = dyn[i].d_un.d_val; break;
            case DT_RELAENT: relocation_entry_size = dyn[i].d_un.d_val; break;
            default:         break;
        }
    }


    if(relocation_table == 0 && relocation_table_size == 0 && relocation_entry_size == 0) {
        // nothing to relocate
        return EFI_SUCCESS;
    }

    // DT_RELA requires DT_RELASZ and DT_RELAENT to also be present
    if(relocation_table == 0 || relocation_table_size == 0 || relocation_entry_size == 0) return EFI_LOAD_ERROR;
    if(relocation_table_size % relocation_entry_size != 0) return EFI_LOAD_ERROR;

    size_t relocation_count = relocation_table_size / relocation_entry_size;

    for(size_t i = 0; i < relocation_count; ++i) {
        Elf64_Rela* relocation = (Elf64_Rela*) (relocation_table + (i * relocation_entry_size));
        uint64_t type = ELF64_R_TYPE(relocation->r_info);

        switch(type) {
            case RELOC_NONE: break;
            case RELOC_RELATIVE:
                if(relocation->r_offset < 0x1000) { return EFI_LOAD_ERROR; }
                uintptr_t* target = (uintptr_t*) (load_base + relocation->r_offset);
                *target = load_base + relocation->r_addend;
                break;
            default: return EFI_LOAD_ERROR;
        }
    }

    return EFI_SUCCESS;
}

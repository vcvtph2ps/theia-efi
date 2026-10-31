// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps
#pragma once

#include <efi/efi_types.h>

#define RISCV_EFI_BOOT_PROTOCOL_GUID { 0xccd15fec, 0x6f73, 0x4eec, { 0x83, 0x95, 0x3e, 0x69, 0xe4, 0xb9, 0x40, 0xbf } }

typedef struct _RISCV_EFI_BOOT_PROTOCOL RISCV_EFI_BOOT_PROTOCOL;


typedef EFI_STATUS(EFIAPI* EFI_GET_BOOT_HARTID)(IN RISCV_EFI_BOOT_PROTOCOL* This, OUT UINTN* BootHartId);

struct _RISCV_EFI_BOOT_PROTOCOL {
    UINT64 Revision;
    EFI_GET_BOOT_HARTID GetBootHartId;
};

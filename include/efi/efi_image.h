// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps
#pragma once

#include <efi/efi_memory.h>
#include <efi/efi_tables.h>
#include <efi/efi_types.h>

#define EFI_LOADED_IMAGE_PROTOCOL_GUID { 0x5B1B31A1, 0x9562, 0x11d2, { 0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B } }

typedef struct {
    UINT32 Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE* SystemTable;

    // Source location of the image
    EFI_HANDLE DeviceHandle;
    THEIA_EFI_STUBBED(EFI_DEVICE_PATH_PROTOCOL) FilePath;
    VOID* Reserved;

    // Image’s load options
    UINT32 LoadOptionsSize;
    VOID* LoadOptions;

    // Location where image was loaded
    VOID* ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    THEIA_EFI_STUBBED(EFI_IMAGE_UNLOAD) Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

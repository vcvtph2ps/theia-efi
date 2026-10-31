// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps
#pragma once

#include <efi/efi_memory.h>
#include <efi/efi_types.h>

typedef enum {
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
    UINT32 RedMask;
    UINT32 GreenMask;
    UINT32 BlueMask;
    UINT32 ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct {
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    UINT32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* Info;
    UINTN SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN FramebufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;


#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID { 0x9042a9de, 0x23dc, 0x4a38, { 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } }

typedef struct EFI_GRAPHICS_OUTPUT_PROTCOL {
    THEIA_EFI_STUBBED(EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) QueryMode;
    THEIA_EFI_STUBBED(EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) SetMode;
    THEIA_EFI_STUBBED(EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

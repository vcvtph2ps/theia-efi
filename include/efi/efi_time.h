// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps
#pragma once

#include <efi/efi_memory.h>
#include <efi/efi_types.h>

typedef struct {
    UINT16 Year; // 1900 - 9999
    UINT8 Month; // 1 - 12
    UINT8 Day; // 1 - 31
    UINT8 Hour; // 0 - 23
    UINT8 Minute; // 0 - 59
    UINT8 Second; // 0 - 59
    UINT8 Pad1;
    UINT32 Nanosecond; // 0 - 999,999,999
    INT16 TimeZone; // —1440 to 1440 or 2047
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02

#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

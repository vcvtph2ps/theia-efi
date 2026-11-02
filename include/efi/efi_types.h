// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps
#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Standard EFI types
typedef uint8_t UINT8;
typedef int8_t INT8;

typedef uint16_t UINT16;
typedef int16_t INT16;

typedef uint32_t UINT32;
typedef int32_t INT32;

typedef uint64_t UINT64;
typedef int64_t INT64;

typedef uint64_t UINTN;
typedef int64_t INTN;

typedef unsigned char CHAR8;
typedef uint16_t CHAR16;

typedef UINT64 EFI_LBA;

typedef UINTN EFI_STATUS;
#define WCHAR CHAR16

#undef VOID
typedef void VOID;
typedef VOID* EFI_HANDLE;

// EFIAPI bullshit...
#if defined(__x86_64__)
#define EFIAPI __attribute__((__ms_abi__))
#else
#define EFIAPI
#endif

#define CONST const
#define IN
#define OUT
#define OPTIONAL

#define THEIA_EFI_STUBBED(x) VOID*

typedef bool BOOLEAN;
#define TRUE true
#define FALSE false

typedef struct {
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

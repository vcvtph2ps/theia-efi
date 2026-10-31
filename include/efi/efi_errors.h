// SPDX-License-Identifier: BSD-1-Clause
// Copyright (c) 2026, vcvtph2ps
#pragma once

#include <efi/efi_types.h>

#define EFI_ERROR(a) (((INTN) a) < 0)

#define EFI_STATUS_ERROR(a) (0x8000000000000000 | a)
#define EFI_STATUS_ERROR_MASK 0x8000000000000000

// The operation completed successfully.
#define EFI_SUCCESS 0

// The image failed to load.
#define EFI_LOAD_ERROR EFI_STATUS_ERROR(1)

// A parameter was incorrect.
#define EFI_INVALID_PARAMETER EFI_STATUS_ERROR(2)

// The operation is not supported.
#define EFI_UNSUPPORTED EFI_STATUS_ERROR(3)

// The buffer was not the proper size for the request.
#define EFI_BAD_BUFFER_SIZE EFI_STATUS_ERROR(4)

// The buffer is not large enough to hold the requested data. The required
// buffer size is returned in the appropriate parameter when this error occurs.
#define EFI_BUFFER_TOO_SMALL EFI_STATUS_ERROR(5)

// There is no data pending upon return.
#define EFI_NOT_READY EFI_STATUS_ERROR(6)

// The physical device reported an error while attempting the operation.
#define EFI_DEVICE_ERROR EFI_STATUS_ERROR(7)

// The device cannot be written to.
#define EFI_WRITE_PROTECTED EFI_STATUS_ERROR(8)

// A resource has run out.
#define EFI_OUT_OF_RESOURCES EFI_STATUS_ERROR(9)

// An inconstancy was detected on the file system causing the operating to fail.
#define EFI_VOLUME_CORRUPTED EFI_STATUS_ERROR(10)

// There is no more space on the file system.
#define EFI_VOLUME_FULL EFI_STATUS_ERROR(11)

// The device does not contain any medium to perform the operation.
#define EFI_NO_MEDIA EFI_STATUS_ERROR(12)

// The medium in the device has changed since the last access.
#define EFI_MEDIA_CHANGED EFI_STATUS_ERROR(13)

// The item was not found.
#define EFI_NOT_FOUND EFI_STATUS_ERROR(14)

// Access was denied.
#define EFI_ACCESS_DENIED EFI_STATUS_ERROR(15)

// The server was not found or did not respond to the request.
#define EFI_NO_RESPONSE EFI_STATUS_ERROR(16)

// A mapping to a device does not exist.
#define EFI_NO_MAPPING EFI_STATUS_ERROR(17)

// The timeout time expired.
#define EFI_TIMEOUT EFI_STATUS_ERROR(18)

// The protocol has not been started.
#define EFI_NOT_STARTED EFI_STATUS_ERROR(19)

// The protocol has already been started.
#define EFI_ALREADY_STARTED EFI_STATUS_ERROR(20)

// The operation was aborted.
#define EFI_ABORTED EFI_STATUS_ERROR(21)

// An ICMP error occurred during the network operation.
#define EFI_ICMP_ERROR EFI_STATUS_ERROR(22)

// A TFTP error occurred during the network operation.
#define EFI_TFTP_ERROR EFI_STATUS_ERROR(23)

// A protocol error occurred during the network operation.
#define EFI_PROTOCOL_ERROR EFI_STATUS_ERROR(24)

// The function encountered an internal version that was incompatible with a
// version requested by the caller.
#define EFI_INCOMPATIBLE_VERSION EFI_STATUS_ERROR(25)

// The function was not performed due to a security violation.
#define EFI_SECURITY_VIOLATION EFI_STATUS_ERROR(26)

// A CRC error was detected.
#define EFI_CRC_ERROR EFI_STATUS_ERROR(27)

// Beginning or end of media was reached.
#define EFI_END_OF_MEDIA EFI_STATUS_ERROR(28)

// The end of the file was reached.
#define EFI_END_OF_FILE EFI_STATUS_ERROR(31)

// The language specified was invalid.
#define EFI_INVALID_LANGUAGE EFI_STATUS_ERROR(32)

// The security status of the data is unknown or compromised and the data must
// be updated or replaced to restore a valid security status.
#define EFI_COMPROMISED_DATA EFI_STATUS_ERROR(33)

// There is an address conflict address allocation
#define EFI_IP_ADDRESS_CONFLICT EFI_STATUS_ERROR(34)

//  A HTTP error occurred during the network operation.
#define EFI_HTTP_ERROR EFI_STATUS_ERROR(35)

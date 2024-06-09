//###########################################################################
// uefi.h
// Declarations of the uefi
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __UEFI_H__
#define __UEFI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "stdint.h"

/**************************** DEFINES ******************************/

/// @brief Common UEFI Data Types
typedef uint8_t  BOOLEAN;
#ifndef __X86_X64__
typedef int32_t  INTN;
typedef uint32_t UINTN;
#else
typedef int64_t  INTN;
typedef uint64_t UINTN;
#endif
typedef int8_t    INT8;
typedef uint8_t   UINT8;
typedef int16_t   INT16;
typedef uint16_t  UINT16;
typedef int32_t   INT32;
typedef uint32_t  UINT32;
typedef int64_t   INT64;
typedef uint64_t  UINT64;
//typedef int128_t  INT128;
//typedef uint128_t UINT128;
typedef char      CHAR8;
typedef wchar_t   CHAR16;
typedef void      VOID;
typedef UINTN     EFI_STATUS;
typedef void*     EFI_HANDLE;
typedef void*     EFI_EVENT;
typedef UINT64    EFI_LBA;
typedef UINTN     EFI_TPL;

/// @brief EFI_GUID
typedef struct {
	UINT32  data1;
	UINT32  data2;
	UINT32  data3;
	UINT8   data4[8];
} EFI_GUID;


/// @brief BOOLEAN
#define FALSE 0
#define TRUE  1


/// @brief Prototype argument decoration for EFI parameters to indicate their direction
/// @param IN - Datum is passed to the function.
/// @param OUT - Datum is returned from the function.
/// @param OPTIONAL - Passing the datum to the function is optional, and a NULL may be passed if the value is not supplied.
/// @param CONST - Datum is read-only.
/// @param EFIAPI Defines the calling convention for UEFI interfaces.Defines the calling convention for UEFI interfaces.
#define IN
#define OUT
#define OPTIONAL
#define CONST
#define EFIAPI


/// @brief EFI ERROR CODE
#define EFI_ERROR(a)                    (((INTN) a) < 0)
#define EFI_SUCCESS                               0
#define EFI_LOAD_ERROR                  EFI_ERROR(1)
#define EFI_INVALID_PARAMETER           EFI_ERROR(2)
#define EFI_UNSUPPORTED                 EFI_ERROR(3)
#define EFI_BAD_BUFFER_SIZE             EFI_ERROR(4)
#define EFI_BUFFER_TOO_SMALL            EFI_ERROR(5)
#define EFI_NOT_READY                   EFI_ERROR(6)
#define EFI_DEVICE_ERROR                EFI_ERROR(7)
#define EFI_WRITE_PROTECTED             EFI_ERROR(8)
#define EFI_OUT_OF_RESOURCES            EFI_ERROR(9)
#define EFI_VOLUME_CORRUPTED            EFI_ERROR(10)
#define EFI_VOLUME_FULL                 EFI_ERROR(11)
#define EFI_NO_MEDIA                    EFI_ERROR(12)
#define EFI_MEDIA_CHANGED               EFI_ERROR(13)
#define EFI_NOT_FOUND                   EFI_ERROR(14)
#define EFI_ACCESS_DENIED               EFI_ERROR(15)
#define EFI_NO_RESPONSE                 EFI_ERROR(16)
#define EFI_NO_MAPPING                  EFI_ERROR(17)
#define EFI_TIMEOUT                     EFI_ERROR(18)
#define EFI_NOT_STARTED                 EFI_ERROR(19)
#define EFI_ALREADY_STARTED             EFI_ERROR(20)
#define EFI_ABORTED                     EFI_ERROR(21)
#define EFI_ICMP_ERROR                  EFI_ERROR(22)
#define EFI_TFTP_ERROR                  EFI_ERROR(23)
#define EFI_PROTOCOL_ERROR              EFI_ERROR(24)
#define EFI_INCOMPATIBLE_VERSION        EFI_ERROR(25)
#define EFI_SECURITY_VIOLATION          EFI_ERROR(26)
#define EFI_CRC_ERROR                   EFI_ERROR(27)
#define EFI_END_OF_MEDIA                EFI_ERROR(28)
#define EFI_END_OF_FILE                 EFI_ERROR(31)
#define EFI_INVALID_LANGUAGE            EFI_ERROR(32)
#define EFI_COMPROMISED_DATA            EFI_ERROR(33)
#define EFI_IP_ADDRESS_CONFLICT         EFI_ERROR(34)
#define EFI_HTTP_ERROR                  EFI_ERROR(35)


/// @brief EFI WARN CODE
#define EFI_WARN(a)                             (a)
#define EFI_WARN_UNKOWN_GLYPH           EFI_WARN(1)
#define EFI_WARN_UNKNOWN_GLYPH          EFI_WARN(1)
#define EFI_WARN_DELETE_FAILURE         EFI_WARN(2)
#define EFI_WARN_WRITE_FAILURE          EFI_WARN(3)
#define EFI_WARN_BUFFER_TOO_SMALL       EFI_WARN(4)
#define EFI_WARN_STALE_DATA             EFI_WARN(5)
#define EFI_WARN_FILE_SYSTEM            EFI_WARN(6)
#define EFI_WARN_RESET_REQUIRED         EFI_WARN(7)


/// @brief EFI_UNUSED
#define EFI_UNUSED                      __attribute__((__unused__))


/************************* EFI_TABLE_HEADER **************************/

/// @brief EFI_TABLE_HEADER
typedef struct {
	UINT64   Signature;
	UINT32   Revision;
	UINT32   HeaderSize;
	UINT32   CRC32;
	UINT32   Reserved;
} EFI_TABLE_HEADER;


/******************** EFI_SIMPLE_TEXT_INPUT_PROTOCOL *****************/

/// @brief Declaration structure
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


/// @brief EFI_INPUT_KEY
typedef struct {
	UINT16                             ScanCode;
	CHAR16                             UnicodeChar;
} EFI_INPUT_KEY;


/// @brief EFI_INPUT_RESET
typedef 
EFI_STATUS 
(EFIAPI *EFI_INPUT_RESET) (
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This, 
	IN BOOLEAN                         ExtendedVerification
);


/// @brief EFI_INPUT_READ_KEY
typedef 
EFI_STATUS 
(EFIAPI *EFI_INPUT_READ_KEY) (
	IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT EFI_INPUT_KEY                  *Key
);


/// @brief EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
{0x387477c1,0x69c7,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}


/// @brief EFI_SIMPLE_TEXT_INPUT_PROTOCOL
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET                    Reset;
	EFI_INPUT_READ_KEY                 ReadKeyStroke;
	EFI_EVENT                          WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


/******************* EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *****************/

/// @brief Declaration structure
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


/// @brief EFI_TEXT_RESET
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_RESET) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN                         ExtendedVerification
);


/// @brief EFI_TEXT_OUTPUT_STRING
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_OUTPUT_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16                          *String
);


/// @brief EFI_TEXT_TEST_STRING
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_TEST_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN CHAR16                          *String
);


/// @brief EFI_TEXT_QUERY_MODE
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_QUERY_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           ModeNumber,
	OUT UINTN                          *Columns,
	OUT UINTN                          *Rows
);


/// @brief EFI_TEXT_SET_MODE
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_SET_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           ModeNumber
);


/// @brief EFI_TEXT_SET_ATTRIBUTE
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Attribute
);


/// @brief EFI_TEXT_CLEAR_SCREEN
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
);


/// @brief EFI_TEXT_SET_CURSOR_POSITION
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN                           Column,
	IN UINTN                           Row
);


/// @brief EFI_TEXT_ENABLE_CURSOR
typedef 
EFI_STATUS 
(EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN                         Enable
);


/// @brief SIMPLE_TEXT_OUTPUT_MODE
typedef struct {
	INT32                              MaxMode;
	//Current settings
	INT32                              Mode;
	INT32                              Attribute;
	INT32                              CursorColumn;
	INT32                              CursorRow;
	BOOLEAN                            CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;


/// @brief EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID
#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
{0x387477c2,0x69c7,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}


/// @brief EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET                     Reset;

	EFI_TEXT_OUTPUT_STRING             OutputString;
	EFI_TEXT_TEST_STRING               TestString;

	EFI_TEXT_QUERY_MODE                QueryMode;
	EFI_TEXT_SET_MODE                  SetMode;
	EFI_TEXT_SET_ATTRIBUTE             SetAttribute;

	EFI_TEXT_CLEAR_SCREEN              ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION       SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR             EnableCursor;

	//Current mode      
	SIMPLE_TEXT_OUTPUT_MODE            *Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


/************************* EFI_BOOT_SERVICES ***********************/

/// @brief EFI_TIME
typedef struct {
	UINT16                             Year;
	UINT8                              Month;
	UINT8                              Day;
	UINT8                              Hour;
	UINT8                              Minute;
	UINT8                              Second;
	UINT8                              Pad1;
	UINT32                             Nanosecond;
	INT16                              TimeZone;
	UINT8                              DayLight;
	UINT8                              Pad2;
} EFI_TIME;


/// @brief EFI_TIME_CAPABILITIES
typedef struct {
	UINT32                             Resolution;
	UINT32                             Accuraccy;
	BOOLEAN                            SetsToZero;
} EFI_TIME_CAPABILITIES;


/// @brief EFI_GET_TIME
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_TIME) (
	OUT EFI_TIME                       *Time,
	OUT EFI_TIME_CAPABILITIES          *Capabilities OPTIONAL
);


/// @brief EFI_SET_TIME
typedef 
EFI_STATUS 
(EFIAPI *EFI_SET_TIME) (
	IN EFI_TIME                        *Time
);


/// @brief EFI_GET_WAKEUP_TIME
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_WAKEUP_TIME) (
	OUT BOOLEAN                        *Enabled,
	OUT BOOLEAN                        *Pending,
	OUT BOOLEAN                        *Time
);


/// @brief EFI_SET_WAKEUP_TIME
typedef 
EFI_STATUS 
(EFIAPI *EFI_SET_WAKEUP_TIME) (
	IN BOOLEAN                         Enabled,
	IN BOOLEAN                         *Time OPTIONAL
);


/// @brief EFI_MEMORY_DESCRIPTOR
typedef struct {
	UINT32                             Type;
	UINT32                             Pad;
	UINT64                             PhysiccalStart;
	UINT64                             VirtualStart;
	UINT64                             NumberOfPages;
	UINT64                             Attribute;
} EFI_MEMORY_DESCRIPTOR;


/// @brief EFI_SET_VIRTUAL_ADDRESS_MAP
typedef 
EFI_STATUS 
(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
	IN UINTN                           MemoryMapSize,
	IN UINTN                           DescriptorSize,
	IN UINT32                          DescriptorVersion, 
	IN EFI_MEMORY_DESCRIPTOR           *VirtualMap
);


/// @brief EFI_CONVERT_POINTER
typedef 
EFI_STATUS 
(EFIAPI *EFI_CONVERT_POINTER) (
	IN UINTN                           DebugDisposition, 
	IN OUT VOID                        **Address
);


/// @brief EFI_GET_VARIABLE
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_VARIABLE) (
	IN CHAR16                          *VariableName,
	IN EFI_GUID                        *VendorGuid,
	OUT UINT32                         *Attributes OPTIONAL,
	IN OUT UINTN                       *DataSize,
	OUT VOID                           *Data
);


/// @brief EFI_GET_NEXT_VARIABLE_NAME
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME) (
	IN OUT UINTN                       *VariableNameSize, 
	IN OUT CHAR16                      *VariableName,
	IN OUT EFI_GUID                    *VendorGuid
);


/// @brief EFI_SET_VARIABLE
typedef 
EFI_STATUS 
(EFIAPI *EFI_SET_VARIABLE) (
	IN CHAR16                          *VariableName,
	IN EFI_GUID                        *VendorGuid,
	IN UINT32                          Attributes,
	IN UINTN                           DataSize,
	IN VOID                            *Data
);


/// @brief EFI_GET_NEXT_HIGHMONO_COUNT
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_NEXT_HIGHMONO_COUNT) (
	OUT UINT32                         *HighCount
);


/// @brief EFI_RESET_TYPE
typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown
} EFI_RESET_TYPE;


/// @brief EFI_CAPSULE_HEADER
typedef struct {
	EFI_GUID                           CapsuleGuid;
	UINT32                             HeaderSize;
	UINT32                             Flags;
	UINT32                             CapsuleImageSize;
} EFI_CAPSULE_HEADER;


/// @brief EFI_RESET_SYSTEM
typedef 
EFI_STATUS 
(EFIAPI *EFI_RESET_SYSTEM) (
	IN EFI_RESET_TYPE                  ResetType, 
	IN EFI_STATUS                      ResetStatus, 
	IN UINTN                           DataSize, 
	IN CHAR16                          *ResetData
);


/// @brief EFI_UPDATE_CAPSULE
typedef 
EFI_STATUS 
(EFIAPI *EFI_UPDATE_CAPSULE) (
	IN EFI_CAPSULE_HEADER              **CapsuleHeaderArray,
	IN UINTN                           CapsuleCount,
	IN UINT64                          ScatterGatherList OPTIONAL
);


/// @brief EFI_QUERY_CAPSULE_CAPABILITIES
typedef 
EFI_STATUS 
(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES) (
	IN EFI_CAPSULE_HEADER              **CapsuleHeaderArray,
	IN UINTN                           CapsuleCount,
	OUT UINT64                         *MaximumCapsuleSize,
	OUT EFI_RESET_TYPE                 *ResetType
);


/// @brief EFI_QUERY_VARIABLE_INFO
typedef 
EFI_STATUS 
(EFIAPI *EFI_QUERY_VARIABLE_INFO) (
	IN UINT32                          Attributes,
	OUT UINT64                         *MaximumVariableStorageSize,
	OUT UINT64                         *RemainingVariableStorageSize,
	OUT UINT64                         *MaximumVariableSize
);


/// @brief EFI_RUNTIME_SERVICES Defines
#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION


/// @brief EFI_RUNTIME_SERVICES
typedef struct {
	EFI_TABLE_HEADER                   Hdr;

	//
	// Time Services
	//
	EFI_GET_TIME                       GetTime;
	EFI_SET_TIME                       SetTime;
	EFI_GET_WAKEUP_TIME                GetWakeupTime;
	EFI_SET_WAKEUP_TIME                SetWakeupTime;

	//
	// Virtual Memory Services
	//
	EFI_SET_VIRTUAL_ADDRESS_MAP        SetVirtualAdderssMap;
	EFI_CONVERT_POINTER                ConvertPointer;

	//
	// Variable Services
	//
	EFI_GET_VARIABLE                   GetVariable;
	EFI_GET_NEXT_VARIABLE_NAME         GetNextVariableName;
	EFI_SET_VARIABLE                   SetVariable;

	//
	// Miscellaneous Services
	//
	EFI_GET_NEXT_HIGHMONO_COUNT        GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM                   ResetSystem;

	//
	// UEFI 2.0 Capsule Services
	//
	EFI_UPDATE_CAPSULE                 UpdateCapsule;
	EFI_QUERY_CAPSULE_CAPABILITIES     QueryCapsuleCapabilities;

	//
	// Miscellaneous UEFI 2.0 Service
	//
	EFI_QUERY_VARIABLE_INFO            QueryVariableInfo;
} EFI_RUNTIME_SERVICES;


/********************** EFI_RUNTIME_SERVICES **********************/

/// @brief EFI_RAISE_TPL
typedef 
EFI_STATUS 
(EFIAPI *EFI_RAISE_TPL) (
	IN EFI_TPL                         NewTPL
);


/// @brief EFI_RESTORE_TPL
typedef 
EFI_STATUS 
(EFIAPI *EFI_RESTORE_TPL) (
	IN EFI_TPL                         OldTPL
);


/// @brief EFI_ALLOCATE_TYPE
typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress
} EFI_ALLOCATE_TYPE;


/// @brief EFI_MEMORY_TYPE
typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;


/// @brief EFI_ALLOCATE_PAGES
typedef 
EFI_STATUS 
(EFIAPI *EFI_ALLOCATE_PAGES) (
	IN EFI_ALLOCATE_TYPE               Type,
	IN EFI_MEMORY_TYPE                 MemoryType,
	IN UINTN                           NoPages,
	OUT UINT64                         *Memory
);


/// @brief EFI_FREE_PAGES
typedef 
EFI_STATUS 
(EFIAPI *EFI_FREE_PAGES) (
	IN UINT64                          Memory,
	IN UINTN                           NoPages
);


/// @brief EFI_GET_MEMORY_MAP
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_MEMORY_MAP) (
	IN OUT UINTN                       *MemoryMapSize,
	IN OUT EFI_MEMORY_DESCRIPTOR       *MemoryMap,
	OUT UINTN                          *MapKey,
	OUT UINTN                          *DescriptorSize,
	OUT UINT32                         *DescriptorVersion
);


/// @brief EFI_ALLOCATE_POOL
typedef 
EFI_STATUS 
(EFIAPI *EFI_ALLOCATE_POOL) (
	IN EFI_MEMORY_TYPE                 PoolType,
	IN UINTN                           Size,
	OUT VOID                           **Buffer
);


/// @brief EFI_FREE_POOL
typedef 
EFI_STATUS 
(EFIAPI *EFI_FREE_POOL) (
	IN void                            *Buffer
);


/// @brief EFI_EVENT_NOTIFY
typedef 
VOID 
(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT                       Event,
	IN VOID                            *Context
);


/// @brief EFI_CREATE_EVENT
typedef 
EFI_STATUS 
(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32                          Type,
	IN EFI_TPL                         NotifyTPL,
	IN EFI_EVENT_NOTIFY                NotifyFunction,
	IN VOID                            *NotifyContext,
	OUT EFI_EVENT                      *Event
);


/// @brief EFI_TIMER_DELAY
typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative,
    TimerTypeMax
} EFI_TIMER_DELAY;


/// @brief EFI_SET_TIMER
typedef 
EFI_STATUS 
(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT                       Event,
	IN EFI_TIMER_DELAY                 Type,
	IN UINT64                          TriggerTime
);


/// @brief EFI_WAIT_FOR_EVENT
typedef 
EFI_STATUS 
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN                           NumberOfEvents,
	IN EFI_EVENT                       *Event,
	OUT UINTN                          *Index
);


/// @brief EFI_SIGNAL_EVENT
typedef 
EFI_STATUS 
(EFIAPI *EFI_SIGNAL_EVENT) (
	IN EFI_EVENT                       Event
);


/// @brief EFI_CLOSE_EVENT
typedef 
EFI_STATUS 
(EFIAPI *EFI_CLOSE_EVENT) (
	IN EFI_EVENT                       Event
);


/// @brief EFI_CHECK_EVENT
typedef 
EFI_STATUS 
(EFIAPI *EFI_CHECK_EVENT) (
	IN EFI_EVENT                       Event
);


/// @brief EFI_INTERFACE_TYPE
typedef enum {
	EFINativeInterface,
	EFIPcodeInterface
} EFI_INTERFACE_TYPE;


/// @brief EFI_LOCATE_SEARCH_TYPE
typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;


/// @brief EFI_DEVICE_PATH
typedef struct {
	UINT8 type;
	UINT8 subType;
	UINT8 length[2];
} EFI_DEVICE_PATH;


/// @brief EFI_INSTALL_PROTOCOL_INTERFACE
typedef 
EFI_STATUS 
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
	IN OUT EFI_HANDLE                  *Handle,
	IN EFI_GUID                        *Protoccol,
	IN EFI_INTERFACE_TYPE              InterfaceType,
	IN VOID                            *Interface
);


/// @brief EFI_REINSTALL_PROTOCOL_INTERFACE
typedef 
EFI_STATUS 
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE                      Handle,
	IN EFI_GUID                        *Protocol,
	IN VOID                            *OldInterface,
	IN VOID                            *NewInterface
);


/// @brief EFI_UNINSTALL_PROTOCOL_INTERFACE
typedef 
EFI_STATUS 
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE                      Handle,
	IN EFI_GUID                        *Protocol,
	IN VOID                            *Interface
);


/// @brief EFI_HANDLE_PROTOCOL
typedef 
EFI_STATUS 
(EFIAPI *EFI_HANDLE_PROTOCOL) (
	IN EFI_HANDLE                      Handle,
	IN EFI_GUID                        *Protocol,
	OUT VOID                           **Interface
);


/// @brief EFI_REGISTER_PROTOCOL_NOTIFY
typedef 
EFI_STATUS 
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
	IN EFI_GUID                        *Protocol,
	IN EFI_EVENT                       Event,
	OUT VOID                           **Registration
);


/// @brief EFI_LOCATE_HANDLE
typedef 
EFI_STATUS 
(EFIAPI *EFI_LOCATE_HANDLE) (
	IN EFI_LOCATE_SEARCH_TYPE          SearchType,
	IN EFI_GUID                        *Protocol,
	IN VOID                            *SearchKey,
	IN OUT UINTN                       *BufferSize,
	OUT EFI_HANDLE                     *Buffer
);


/// @brief EFI_LOCATE_DEVICE_PATH
typedef 
EFI_STATUS 
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
	IN EFI_GUID                        *Protocol,
	IN OUT EFI_DEVICE_PATH             **DevicePath,
	OUT EFI_HANDLE                     *Device
);


/// @brief EFI_INSTALL_CONFIGURATION_TABLE
typedef 
EFI_STATUS 
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
	IN EFI_GUID                        *Guid,
	IN VOID                            *Table
);


/// @brief EFI_IMAGE_LOAD
typedef 
EFI_STATUS 
(EFIAPI *EFI_IMAGE_LOAD) (
	IN BOOLEAN                         BootPolicy,
	IN EFI_HANDLE                      ParentImageHandle,
	IN EFI_DEVICE_PATH                 *FilePath,
	IN VOID                            *SourceBuffer OPTIONAL, 
	IN UINTN                           SourceSize,
	OUT EFI_HANDLE                     *ImageHandle
);


/// @brief EFI_IMAGE_START
typedef 
EFI_STATUS 
(EFIAPI *EFI_IMAGE_START) (
	IN EFI_HANDLE                      ImageHandle,
	OUT UINTN                          *ExitDataSize,
	OUT CHAR16                         **ExitData OPTIONAL
);


/// @brief EFI_EXIT
typedef 
EFI_STATUS 
(EFIAPI *EFI_EXIT) (
	IN EFI_HANDLE                      ImageHandle,
	IN EFI_STATUS                      ExitStatus,
	IN UINTN                           ExitDataSize,
	IN CHAR16                          *ExitData OPTIONAL
);


/// @brief EFI_IMAGE_UNLOAD
typedef 
EFI_STATUS 
(EFIAPI *EFI_IMAGE_UNLOAD) (
	IN EFI_HANDLE                      ImageHandle
);


/// @brief EFI_EXIT_BOOT_SERVICES
typedef 
EFI_STATUS 
(EFIAPI *EFI_EXIT_BOOT_SERVICES) (
	IN EFI_HANDLE                      ImageHandle,
	IN UINTN                           MapKey
);


/// @brief EFI_GET_NEXT_MONOTONIC_COUNT
typedef 
EFI_STATUS 
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
	OUT UINT64                         *Count
);


/// @brief EFI_STALL
typedef 
EFI_STATUS 
(EFIAPI *EFI_STALL) (
	IN UINTN                           Microseconds
);


/// @brief EFI_SET_WATCHDOG_TIMER
typedef 
EFI_STATUS 
(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
	IN UINTN                           Timeout,
	IN UINT64                          WatchdogCode,
	IN UINTN                           DataSize,
	IN CHAR16                          *WatchdogData OPTIONAL
);


/// @brief EFI_CONNECT_CONTROLLER
typedef 
EFI_STATUS 
(EFIAPI *EFI_CONNECT_CONTROLLER) (
	IN EFI_HANDLE                      ControllerHandle,
	IN EFI_HANDLE                      *DriverImageHandle OPTIONAL, 
	IN EFI_DEVICE_PATH                 *RemainingDevicePath OPTIONAL, 
	IN BOOLEAN                         Recursive
);


/// @brief EFI_DISCONNECT_CONTROLLER
typedef 
EFI_STATUS 
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
	IN EFI_HANDLE                      ControllerHandle,
	IN EFI_HANDLE                      DriverImageHandle OPTIONAL, 
	IN EFI_HANDLE                      ChildHandle OPTIONAL
);


/// @brief EFI_OPEN_PROTOCOL
typedef 
EFI_STATUS 
(EFIAPI *EFI_OPEN_PROTOCOL) (
	IN EFI_HANDLE                      Handle,
	IN EFI_GUID                        *Protocol,
	OUT VOID                           **Interface OPTIONAL, 
	IN EFI_HANDLE                      AgentHandle,
	IN EFI_HANDLE                      ControllerHandle,
	IN UINT32                          Attributes
);


/// @brief EFI_CLOSE_PROTOCOL
typedef 
EFI_STATUS 
(EFIAPI *EFI_CLOSE_PROTOCOL) (
	IN EFI_HANDLE                      Handle,
	IN EFI_GUID                        *Protocol,
	IN EFI_HANDLE                      *AgentHandle,
	IN EFI_HANDLE                      ControllerHandle
);


/// @brief EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
typedef struct {
	EFI_HANDLE                         AgentHandle;
	EFI_HANDLE                         ControllerHandle;
	UINT32                             Attributes;
	UINT32                             OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;


/// @brief EFI_OPEN_PROTOCOL_INFORMATION
typedef 
EFI_STATUS 
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
	IN EFI_HANDLE                            Handle,
	OUT EFI_GUID                             *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY  **EntryBuffer,
	OUT UINTN                                *EntryCount
);


/// @brief EFI_PROTOCOLS_PER_HANDLE
typedef 
EFI_STATUS 
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
	IN EFI_HANDLE                      Handle,
	OUT EFI_GUID                       ***ProtocolBuffer,
	OUT UINTN                          *ProtocolBufferCount
);


/// @brief EFI_LOCATE_HANDLE_BUFFER
typedef 
EFI_STATUS 
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
	IN EFI_LOCATE_SEARCH_TYPE          SearchType,
	IN EFI_GUID                        *Protoccol,
	IN VOID                            *SearchKey,
	IN OUT UINTN                       *NoHndles,
	OUT EFI_HANDLE                     **Buffer
);


/// @brief EFI_LOCATE_PROTOCOL
typedef 
EFI_STATUS 
(EFIAPI *EFI_LOCATE_PROTOCOL) (
	IN EFI_GUID                        *Protocol,
	IN VOID                            *Registration,
	OUT VOID                           **Interface
);


/// @brief EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES
typedef 
EFI_STATUS 
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE                 *Handle,
	...
);


/// @brief EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES
typedef 
EFI_STATUS 
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE                 Handle,
	...
);


/// @brief EFI_CALCULATE_CRC32
typedef 
EFI_STATUS 
(EFIAPI *EFI_CALCULATE_CRC32) (
	IN VOID                           *Data,
	IN UINTN                          DataSize,
	OUT UINT32                        *CRC32
);


/// @brief EFI_COPY_MEM
typedef void (*EFI_COPY_MEM) (
	IN VOID                           *Destionation,
	IN VOID                           *Source,
	IN UINTN                          Length
);


/// @brief EFI_SET_MEM
typedef void (*EFI_SET_MEM) (
	IN VOID                           *Buffer,
	IN UINTN                          Size,
	IN UINT8                          Value
);


/// @brief EFI_CREATE_EVENT_EX
typedef 
EFI_STATUS 
(EFIAPI *EFI_CREATE_EVENT_EX) (
	IN UINT32                         Type,
	IN EFI_TPL                        NotifyTPL,
	IN EFI_EVENT_NOTIFY               NotifyFunction,
	IN const VOID                     *NotifyContext,
	IN const EFI_GUID                 *EventGroup,
	OUT EFI_EVENT                     *Event
);


/// @brief EFIBootServices
typedef struct {
	EFI_TABLE_HEADER                  Hdr;
	
	//
	// Task Priority Services
	//
	EFI_RAISE_TPL                     RaiseTPL;
	EFI_RESTORE_TPL                   RestoreTPL;

	//
	// Memory Services
	//
	EFI_ALLOCATE_PAGES                AllocatePages;
	EFI_FREE_PAGES                    FreePages;
	EFI_GET_MEMORY_MAP                GetMemoryMap;
	EFI_ALLOCATE_POOL                 AllocatePool;
	EFI_FREE_POOL                     FreePool;

	//
	// Event & Timer Services
	//
	EFI_CREATE_EVENT                  CreateEvent;
	EFI_SET_TIMER                     SetTimer;
	EFI_WAIT_FOR_EVENT                WaitForEvent;
	EFI_SIGNAL_EVENT                  SignalEvent;
	EFI_CLOSE_EVENT                   CloseEvent;
	EFI_CHECK_EVENT                   CheckEvent;

	//
	// Protocol Handler Services
	//
	EFI_INSTALL_PROTOCOL_INTERFACE    InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE  ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE  UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL               HandleProtocol;
	EFI_HANDLE_PROTOCOL               PCHandleProtocol;
	EFI_REGISTER_PROTOCOL_NOTIFY      RegisterProtocolNotify;
	EFI_LOCATE_HANDLE                 LocateHandle;
	EFI_LOCATE_DEVICE_PATH            LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE   InstallConfigurationTable;

	//
	// Image Services
	//
	EFI_IMAGE_LOAD                    LoadImage;
	EFI_IMAGE_START                   StartImage;
	EFI_EXIT                          Exit;
	EFI_IMAGE_UNLOAD                  UnloadImage;
	EFI_EXIT_BOOT_SERVICES            ExitBootServices;

	//
	// Miscellaneous Services
	//
	EFI_GET_NEXT_MONOTONIC_COUNT      GetNextMonotonicCount;
	EFI_STALL                         Stall;
	EFI_SET_WATCHDOG_TIMER            SetWatchdogTimer;

	//
	// DriverSupport Services
	//
	EFI_CONNECT_CONTROLLER            ConnectController;
	EFI_DISCONNECT_CONTROLLER         DisconnectController;

	//
	// Open and Close Protocol Services
	//
	EFI_OPEN_PROTOCOL                 OpenProtocol;
	EFI_CLOSE_PROTOCOL                CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation;

	//
	// Library Services
	//
	EFI_PROTOCOLS_PER_HANDLE          ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER          LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL               LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES   InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	//
	// 32-bit CRC Services
	//
	EFI_CALCULATE_CRC32               CalculateCrc32;

	//
	// Miscellaneous Services
	//
	EFI_COPY_MEM                      CopyMem;
	EFI_SET_MEM                       SetMem;
	EFI_CREATE_EVENT_EX               CreateEventEx;
} EFI_BOOT_SERVICES;


/********************** EFI_CONFIGURATION_TABLE **********************/


/// @brief EFI_CONFIGURATION_TABLE
typedef struct {
	EFI_GUID                          VendorGuid;
	VOID                              *VendorTable;
} EFI_CONFIGURATION_TABLE;


/************************* EFI_SYSTEM_TABLE **************************/

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION ((2<<16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION  ((2<<16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION  ((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION  ((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION  ((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION  ((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION  ((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION  ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION  ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION  ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION  ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION  ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION  ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION  ((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION EFI_2_100_SYSTEM_TABLE_REVISION

typedef struct {
	EFI_TABLE_HEADER                  Hdr;
	CHAR16                            *FirmwareVendor;
	UINT32                            FirmwareRevision;
	EFI_HANDLE                        ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *ConIn;
	EFI_HANDLE                        ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *ConOut;
	EFI_HANDLE                        StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *StdErr;
	EFI_RUNTIME_SERVICES              *RuntimeServices;
	EFI_BOOT_SERVICES                 *BootServices;
	UINTN                             NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE           *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#ifdef __cplusplus
}
#endif
 
#endif //!__UEFI_H__

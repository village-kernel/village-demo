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
#include "stdbool.h"


/// @brief Defines
typedef void* EFIHandle;
typedef void* EFIEvent;
typedef unsigned int EFIStatus;
typedef unsigned int EFITPL;
typedef unsigned int uintn_t;


/// @brief Prototype argument decoration for EFI parameters to indicate their direction
/// @param IN - argument is passed into the function
/// @param OUT - argument (pointer) is returned from the function
/// @param OPTIONAL - argument is optional
#ifndef IN
    #define IN
    #define OUT
    #define OPTIONAL
#endif


/// @brief EFITableHeader
typedef struct {
	uint64_t   signature;
	uint32_t   revision;
	uint32_t   headerSize;
	uint32_t   crc32;
	uint32_t   reserved;
} EFITableHeader;


/// @brief EFIInputKey
typedef struct {
	uint16_t    scanCode;
	wchar_t     unicodeChar;
} EFIInputKey;


/// @brief EFIInputReset
typedef EFIStatus (*EFIInputReset) (
	IN struct _SimpleTextInputInterface *this, 
	IN bool extendedVerification
);


/// @brief EFIInputReadKey
typedef EFIStatus (*EFIInputReadKey) (
	IN struct _SimpleTextInputInterface *this,
	OUT EFIInputKey *key
);


/// @brief SimpleTextInputInterface
typedef struct _SimpleTextInputInterface {
	EFIInputReset        reset;
	EFIInputReadKey      readKeyStroke;
	EFIEvent             waitForKey;
} SimpleTextInputInterface, EFISimpleTextInProtocol;


/// @brief EFITextReset
typedef EFIStatus (*EFITextReset) (
	IN struct _SimpleTextOutputINterface *this,
	IN bool extendedVerification
);


/// @brief EFITextOutputString
typedef EFIStatus (*EFITextOutputString) (
	IN struct _SimpleTextOutputInterface *this,
	IN wchar_t *string
);


/// @brief EFITextTestString
typedef EFIStatus (*EFITextTestString) (
	IN struct _SimpleTextOutputInterface *this,
	IN wchar_t *string
);


/// @brief EFITextQueryMode
typedef EFIStatus (*EFITextQueryMode) (
	IN struct _SimpleTextOutputInterface *this,
	IN uintn_t modeNumber,
	OUT uintn_t *columns,
	OUT uintn_t *rows
);


/// @brief EFITextSetMode
typedef EFIStatus (*EFITextSetMode) (
	IN struct _SimpleTextOutputInterface *this,
	IN uintn_t modeNumber
);


/// @brief EFITextSetAttribute
typedef EFIStatus (*EFITextSetAttribute) (
	IN struct _SimpleTextOutputInterface *this,
	IN uintn_t attribute
);


/// @brief EFITextClearScreen
typedef EFIStatus (*EFITextClearScreen) (
	IN struct _SimpleTextOutputInterface *this
);


/// @brief EFITextSetCursorPosition
typedef EFIStatus (*EFITextSetCursorPosition) (
	IN struct _SimpleTextOutputInterface *this,
	IN uintn_t column,
	IN uintn_t row
);


/// @brief EFITextEnableCursor
typedef EFIStatus (*EFITextEnableCursor) (
	IN struct _SimpleTextOutputInterface *this,
	IN bool enable
);


/// @brief SimpleTextOutputMode
typedef struct {
	int32_t    maxMode;
	//Current settings
	int32_t    mode;
	int32_t    attribute;
	int32_t    cursorColumn;
	int32_t    cursorRow;
	bool       cursorVisible;
} SimpleTextOutputMode;


/// @brief SimpleTextOutputInterface
typedef struct _SimpleTextOutputInterface {
	EFITextReset             reset;

	EFITextOutputString      outputString;
	EFITextTestString        testString;

	EFITextQueryMode         queryMode;
	EFITextSetMode           setMode;
	EFITextSetAttribute      setAttribute;

	EFITextClearScreen       clearScreen;
	EFITextSetCursorPosition setCursorPosition;
	EFITextEnableCursor      enableCursor;

	//Current mode
	SimpleTextOutputMode     *mode;
} SimpleTextOutputInterface, EFISimpleTextOutProtocol;


/// @brief EFITime
typedef struct {
	uint16_t   year;
	uint8_t    month;
	uint8_t    day;
	uint8_t    hour;
	uint8_t    minute;
	uint8_t    second;
	uint8_t    pad1;
	uint32_t   nanosecond;
	int16_t    timeZone;
	uint8_t    dayLight;
	uint8_t    pad2;
} EFITime;


/// @brief EFITimeCapabilities
typedef struct {
	uint32_t resolution;
	uint32_t accuraccy;
	bool     setsToZero;
} EFITimeCapabilities;


/// @brief EFIGetTime
typedef EFIStatus (*EFIGetTime) (
	OUT EFITime *time,
	OUT EFITimeCapabilities *capabilities OPTIONAL
);


/// @brief EFISetTime
typedef EFIStatus (*EFISetTime) (
	IN EFITime *time
);


/// @brief EFIGetWakeupTime
typedef EFIStatus (*EFIGetWakeupTime) (
	OUT bool *enabled,
	OUT bool *pending,
	OUT bool *time
);


/// @brief EFISetWakeupTime
typedef EFIStatus (*EFISetWakeupTime) (
	IN bool enabled,
	IN bool *time OPTIONAL
);


/// @brief EFIMemoryDescriptor
typedef struct {
	uint32_t   type;
	uint32_t   pad;
	uint64_t   physiccalStart;
	uint64_t   virtualStart;
	uint64_t   numberOfPages;
	uint64_t   attribute;
} EFIMemoryDescriptor;


/// @brief EFIGuid
typedef struct {
	uint32_t  data1;
	uint32_t  data2;
	uint32_t  data3;
	uint8_t   data4[8];
} EFIGuid;


/// @brief EFISetVirtualAddressMap
typedef EFIStatus (*EFISetVirtualAddressMap) (
	IN uintn_t memoryMapSize,
	IN uintn_t descriptorSize,
	IN uint32_t descriptorVersion, 
	IN EFIMemoryDescriptor *virtualMap
);


/// @brief EFIConvertPointer
typedef EFIStatus (*EFIConvertPointer) (
	IN uintn_t debugDisposition, 
	IN OUT void **address
);


/// @brief EFIGetVariable
typedef EFIStatus (*EFIGetVariable) (
	IN wchar_t *variableName,
	IN EFIGuid *vendorGuid,
	OUT uint32_t *attributes, OPTIONAL
	IN OUT uintn_t *dataSize,
	OUT void* data
);


/// @brief EFIGetNextVariableName
typedef EFIStatus (*EFIGetNextVariableName) (
	IN OUT uintn_t *variableNameSize, 
	IN OUT wchar_t *variableName,
	IN OUT EFIGuid *vendorGuid
);


/// @brief EFISetVariable
typedef EFIStatus (*EFISetVariable) (
	IN wchar_t *variableName,
	IN EFIGuid *vendorGuid,
	IN uint32_t attributes,
	IN uintn_t dataSize,
	IN void* data
);


/// @brief EFIGetNextHighMonoCount
typedef EFIStatus (*EFIGetNextHighMonoCount) (
	OUT uint32_t *highCount
);


/// @brief EFIResetType
typedef enum {
	_EfiResetCold,
	_EfiResetWarm,
	_EfiResetShutdown
} EFIResetType;


/// @brief EFICapsuleHeader
typedef struct {
	EFIGuid   capsuleGuid;
	uint32_t  headerSize;
	uint32_t  flags;
	uint32_t  capsuleImageSize;
} EFICapsuleHeader;


/// @brief EFIResetSystem
typedef EFIStatus (*EFIResetSystem) (
	IN EFIResetType resetType, 
	IN EFIStatus resetStatus, 
	IN uintn_t dataSize, 
	IN wchar_t *resetData
);


/// @brief EFIUpdateCapsule
typedef EFIStatus (*EFIUpdateCapsule) (
	IN EFICapsuleHeader **capsuleHeaderArray,
	IN uintn_t capsuleCount,
	IN uint64_t scatterGatherList OPTIONAL
);


/// @brief EFIQueryCapsuleCapabilities
typedef EFIStatus (*EFIQueryCapsuleCapabilities) (
	IN EFICapsuleHeader **capsuleHeaderArray,
	IN uintn_t capsuleCount,
	OUT uint64_t *maximumCapsuleSize,
	OUT EFIResetType *resetType
);


/// @brief EFIQueryVariableInfo
typedef EFIStatus (*EFIQueryVariableInfo) (
	IN uint32_t attributes,
	OUT uint64_t *maximumVariableStorageSize,
	OUT uint64_t *remainingVariableStorageSize,
	OUT uint64_t *maximumVariableSize
);


/// @brief EFIRuntimeServices
typedef struct {
	EFITableHeader                 header;

	//Time services
	EFIGetTime                     GetTime;
	EFISetTime                     SetTime;
	EFIGetWakeupTime               GetWakeupTime;
	EFISetWakeupTime               SetWakeupTime;

	//virtual memory services
	EFISetVirtualAddressMap        SetVirtualAdderssMap;
	EFIConvertPointer              ConvertPointer;

	//Variable services
	EFIGetVariable                 GetVariable;
	EFIGetNextVariableName         GetNextVariableName;
	EFISetVariable                 SetVariable;

	//Misc
	EFIGetNextHighMonoCount        GetNextHighMonotonicCount;
	EFIResetSystem                 ResetSystem;

	EFIUpdateCapsule               UpdateCapsule;
	EFIQueryCapsuleCapabilities    QueryCapsuleCapabilities;
	EFIQueryVariableInfo           QueryVariableInfo;
} EFIRuntimeServices;


/// @brief EFIRaiseTPL
typedef EFIStatus (*EFIRaiseTPL) (
	IN EFITPL newTPL
);


/// @brief EFIRestoreTPL
typedef EFIStatus (*EFIRestoreTPL) (
	IN EFITPL oldTPL
);


/// @brief EFIAllocateType
typedef enum {
	_AllocateAnyPages,
	_AllocateMaxAddress,
	_AllocateAddress
} EFIAllocateType;


/// @brief EFIMemoryType
typedef enum {
    _EfiReservedMemoryType,
    _EfiLoaderCode,
    _EfiLoaderData,
    _EfiBootServicesCode,
    _EfiBootServicesData,
    _EfiRuntimeServicesCode,
    _EfiRuntimeServicesData,
    _EfiConventionalMemory,
    _EfiUnusableMemory,
    _EfiACPIReclaimMemory,
    _EfiACPIMemoryNVS,
    _EfiMemoryMappedIO,
    _EfiMemoryMappedIOPortSpace,
    _EfiPalCode,
    _EfiPersistentMemory,
    _EfiUnacceptedMemoryType,
    _EfiMaxMemoryType
} EFIMemoryType;


/// @brief EFIAllocatePages
typedef EFIStatus (*EFIAllocatePages) (
	IN EFIAllocateType type,
	IN EFIMemoryType memoryType,
	IN uintn_t noPages,
	OUT uint64_t *memory
);


/// @brief EFIFreePages
typedef EFIStatus (*EFIFreePages) (
	IN uint64_t memory,
	IN uintn_t noPages
);


/// @brief EFIGetMemoryMap
typedef EFIStatus (*EFIGetMemoryMap) (
	IN OUT uintn_t *memoryMapSize,
	IN OUT EFIMemoryDescriptor *memoryMap,
	OUT uintn_t *mapKey,
	OUT uintn_t *descriptorSize,
	OUT uint32_t *descriptorVersion
);


/// @brief EFIAllocatePool
typedef EFIStatus (*EFIAllocatePool) (
	IN EFIMemoryType poolType,
	IN uintn_t size,
	OUT void **buffer
);


/// @brief EFIFreePool
typedef EFIStatus (*EFIFreePool) (
	IN void *buffer
);


/// @brief EFIEventNotify
typedef void (*EFIEventNotify) (
	IN EFIEvent event,
	IN void *context
);


/// @brief EFICreateEvent
typedef EFIStatus (*EFICreateEvent) (
	IN uint32_t type,
	IN EFITPL notifyTPL,
	IN EFIEventNotify notifyFunction,
	IN void *notifyContext,
	OUT EFIEvent *event
);


/// @brief EFITimerDelay
typedef enum {
    _TimerCancel,
    _TimerPeriodic,
    _TimerRelative,
    _TimerTypeMax
} EFITimerDelay;


/// @brief EFISetTimer
typedef EFIStatus (*EFISetTimer) (
	IN EFIEvent event,
	IN EFITimerDelay type,
	IN uint64_t triggerTime
);


/// @brief EFIWaitForEvent
typedef EFIStatus (*EFIWaitForEvent) (
	IN uintn_t numberOfEvents,
	IN EFIEvent *event,
	OUT uintn_t *index
);


/// @brief EFISignalEvent
typedef EFIStatus (*EFISignalEvent) (
	IN EFIEvent event
);


/// @brief EFICloseEvent
typedef EFIStatus (*EFICloseEvent) (
	IN EFIEvent event
);


/// @brief EFICheckEvent
typedef EFIStatus (*EFICheckEvent) (
	IN EFIEvent event
);


/// @brief EFIInterfaceType
typedef enum {
	_EFINativeInterface,
	_EFIPcodeInterface
} EFIInterfaceType;


/// @brief EFILocateSearchType
typedef enum {
    _AllHandles,
    _ByRegisterNotify,
    _ByProtocol
} EFILocateSearchType;


/// @brief EFIDevicePath
typedef struct {
	uint8_t type;
	uint8_t subType;
	uint8_t length[2];
} EFIDevicePath;


/// @brief EFIInstallProtocolInterface
typedef EFIStatus (*EFIInstallProtocolInterface) (
	IN OUT EFIHandle *handle,
	IN EFIGuid *protoccol,
	IN EFIInterfaceType interfaceType,
	IN void *interface
);


/// @brief EFIReinstallProtocolInterface
typedef EFIStatus (*EFIReinstallProtocolInterface) (
	IN EFIHandle handle,
	IN EFIGuid *protocol,
	IN void *oldInterface,
	IN void *newInterface
);


/// @brief EFIUninstallProtocolInterface
typedef EFIStatus (*EFIUninstallProtocolInterface) (
	IN EFIHandle handle,
	IN EFIGuid *protocol,
	IN void *interface
);


/// @brief EFIHandleProtocol
typedef EFIStatus (*EFIHandleProtocol) (
	IN EFIHandle handle,
	IN EFIGuid *protocol,
	OUT void **interface
);


/// @brief EFIRegisterProtocolNotify
typedef EFIStatus (*EFIRegisterProtocolNotify) (
	IN EFIGuid *protocol,
	IN EFIEvent event,
	OUT void **registration
);


/// @brief EFILocateHandle
typedef EFIStatus (*EFILocateHandle) (
	IN EFILocateSearchType searchType,
	IN EFIGuid *protocol,
	IN void *searchKey,
	IN OUT uintn_t *bufferSize,
	OUT EFIHandle *buffer
);


/// @brief EFILocateDevicePath
typedef EFIStatus (*EFILocateDevicePath) (
	IN EFIGuid *protocol,
	IN OUT EFIDevicePath **devicePath,
	OUT EFIHandle *device
);


/// @brief EFIInstallConfigurationTable
typedef EFIStatus (*EFIInstallConfigurationTable) (
	IN EFIGuid *guid,
	IN void *table
);


/// @brief EFIImageLoad
typedef EFIStatus (*EFIImageLoad) (
	IN bool bootPolicy,
	IN EFIHandle parentImageHandle,
	IN EFIDevicePath *filePath,
	IN void *sourceBuffer, OPTIONAL
	IN uintn_t sourceSize,
	OUT EFIHandle *imageHandle
);


/// @brief EFIImageStart
typedef EFIStatus (*EFIImageStart) (
	IN EFIHandle imageHandle,
	OUT uintn_t *exitDataSize,
	OUT wchar_t **exitData OPTIONAL
);


/// @brief EFIExit
typedef EFIStatus (*EFIExit) (
	IN EFIHandle imageHandle,
	IN EFIStatus exitStatus,
	IN uintn_t exitDataSize,
	IN wchar_t *exitData OPTIONAL
);


/// @brief EFIImageUnload
typedef EFIStatus (*EFIImageUnload) (
	IN EFIHandle ImageHandle
);


/// @brief EFIExitBootServices
typedef EFIStatus (*EFIExitBootServices) (
	IN EFIHandle imageHandle,
	IN uintn_t mapKey
);


/// @brief EFIGetNextMonotonicCount
typedef EFIStatus (*EFIGetNextMonotonicCount) (
	OUT uint64_t *count
);


/// @brief EFIStall
typedef EFIStatus (*EFIStall) (
	IN uintn_t microseconds
);


/// @brief EFISetWatchdogTimer
typedef EFIStatus (*EFISetWatchdogTimer) (
	IN uintn_t timeout,
	IN uint64_t watchdogCode,
	IN uintn_t dataSize,
	IN wchar_t *watchdogData OPTIONAL
);


/// @brief EFIConnectController
typedef EFIStatus (*EFIConnectController) (
	IN EFIHandle controllerHandle,
	IN EFIHandle *driverImageHandle, OPTIONAL
	IN EFIDevicePath *remainingDevicePath, OPTIONAL
	IN bool recursive
);


/// @brief EFIDisconnectController
typedef EFIStatus (*EFIDisconnectController) (
	IN EFIHandle controllerHandle,
	IN EFIHandle driverImageHandle, OPTIONAL
	IN EFIHandle childHandle OPTIONAL
);


/// @brief EFIOpenProtocol
typedef EFIStatus (*EFIOpenProtocol) (
	IN EFIHandle handle,
	IN EFIGuid *protocol,
	OUT void **interface, OPTIONAL
	IN EFIHandle agentHandle,
	IN EFIHandle controllerHandle,
	IN uint32_t attributes
);


/// @brief EFICloseProtocol
typedef EFIStatus (*EFICloseProtocol) (
	IN EFIHandle handle,
	IN EFIGuid *protocol,
	IN EFIHandle *agentHandle,
	IN EFIHandle controllerHandle
);


/// @brief EFIOpenProtocolInformationEntry
typedef struct {
	EFIHandle    agentHandle;
	EFIHandle    controllerHandle;
	uint32_t     attributes;
	uint32_t     openCount;
} EFIOpenProtocolInformationEntry;


/// @brief EFIOpenProtocolInformation
typedef EFIStatus (*EFIOpenProtocolInformation) (
	IN EFIHandle handle,
	OUT EFIGuid *protocol,
	OUT EFIOpenProtocolInformationEntry **entryBuffer,
	OUT uintn_t *entryCount
);


/// @brief EFIProtocolsPerHandle
typedef EFIStatus (*EFIProtocolsPerHandle) (
	IN EFIHandle handle,
	OUT EFIGuid ***protocolBuffer,
	OUT uintn_t *protocolBufferCount
);


/// @brief EFILocateHandleBuffer
typedef EFIStatus (*EFILocateHandleBuffer) (
	IN EFILocateSearchType searchType,
	IN EFIGuid *protoccol,
	IN void *searchKey,
	IN OUT uintn_t *noHndles,
	OUT EFIHandle **buffer
);


/// @brief EFILocateProtocol
typedef EFIStatus (*EFILocateProtocol) (
	IN EFIGuid *protocol,
	IN void *registration,
	OUT void **interface
);


/// @brief EFIInstallMultipleProtocolInterfaces
typedef EFIStatus (*EFIInstallMultipleProtocolInterfaces) (
	IN OUT EFIHandle *handle,
	...
);


/// @brief EFIUninstallMultipleProtocolInterfaces
typedef EFIStatus (*EFIUninstallMultipleProtocolInterfaces) (
	IN OUT EFIHandle handle,
	...
);


/// @brief EFICalculateCrc32
typedef EFIStatus (*EFICalculateCrc32) (
	IN void *data,
	IN uintn_t dataSize,
	OUT uint32_t *crc32
);


/// @brief EFICopyMemory
typedef void (*EFICopyMemory) (
	IN void *destionation,
	IN void *source,
	IN uintn_t length
);


/// @brief EFISetMemory
typedef void (*EFISetMemory) (
	IN void *buffer,
	IN uintn_t size,
	IN uint8_t value
);


/// @brief EFICreateEventEx
typedef EFIStatus (*EFICreateEventEx) (
	IN uint32_t type,
	IN EFITPL notifyTPL,
	IN EFIEventNotify notifyFunction,
	IN const void *notifyContext,
	IN const EFIGuid *eventGroup,
	OUT EFIEvent *event
);


/// @brief EFIBootServices
typedef struct {
	EFITableHeader                 header;

	//Task priority functions
	EFIRaiseTPL                    RaiseTPL;
	EFIRestoreTPL                  RestoreTPL;

	//Memory functions
	EFIAllocatePages               AllocatePages;
	EFIFreePages                   FreePages;
	EFIGetMemoryMap                GetMemoryMap;
	EFIAllocatePool                AllocatePool;
	EFIFreePool                    FreePool;

	//Event & timer functions
	EFICreateEvent                 CreateEvent;
	EFISetTimer                    SetTimer;
	EFIWaitForEvent                WaitForEvent;
	EFISignalEvent                 SignalEvent;
	EFICloseEvent                  CloseEvent;
	EFICheckEvent                  CheckEvent;

	//Protocol handler functions
	EFIInstallProtocolInterface    InstallProtocolInterface;
	EFIReinstallProtocolInterface  ReinstallProtocolInterface;
	EFIUninstallProtocolInterface  UninstallProtocolInterface;
	EFIHandleProtocol              HandleProtocol;
	EFIHandleProtocol              PCHandleProtocol;
	EFIRegisterProtocolNotify      RegisterProtocolNotify;
	EFILocateHandle                LocateHandle;
	EFILocateDevicePath            LocateDevicePath;
	EFIInstallConfigurationTable   InstallConfigurationTable;

	//Image functions
	EFIImageLoad                   LoadImage;
	EFIImageStart                  StartImageStartImage;
	EFIExit                        Exit;
	EFIImageUnload                 UnloadImage;
	EFIExitBootServices            ExitBootServices;

	//Misc functions
	EFIGetNextMonotonicCount       GetNextMonotonicCount;
	EFIStall                       Stall;
	EFISetWatchdogTimer            SetWatchdogTimer;

	//DriverSupport services
	EFIConnectController           ConnectController;
	EFIDisconnectController        DisconnectController;

	//Open and close protocol services
	EFIOpenProtocol                OpenProtocol;
	EFICloseProtocol               CloseProtocol;
	EFIOpenProtocolInformation     OpenProtocolInformation;

	//Library services
	EFIProtocolsPerHandle          ProtocolsPerHandle;
	EFILocateHandleBuffer          LocateHandleBuffer;
	EFILocateProtocol              LocateProtocol;
	EFIInstallMultipleProtocolInterfaces   InstallMultipleProtocolInterfaces;
	EFIUninstallMultipleProtocolInterfaces UninstallMultipleProtocolInterfaces;

	//32-bit CRC services
	EFICalculateCrc32              CalculateCrc32;

	//Misc services
	EFICopyMemory                  CopyMemory;
	EFISetMemory                   SetMemory;
	EFICreateEventEx               CreateEventEx;
} EFIBootServices;


/// @brief EFIConfigurationTable
typedef struct {
	EFIGuid     vendorGuid;
	void        *vendorTable;
} EFIConfigurationTable;


/// @brief EFISystemTable
typedef struct {
	EFITableHeader                  header;

	wchar_t*                        *firmwareVendor;
    uint32_t                        firmwareRevision;

    EFIHandle                       consoleInHandle;
    SimpleTextInputInterface        *conIn;

    EFIHandle                       consoleOutHandle;
    SimpleTextOutputInterface       *conOut;

    EFIHandle                       standardErrorHandle;
    SimpleTextOutputInterface       *stdErr;

    EFIRuntimeServices              *runtimeServices;
    EFIBootServices                 *bootServices;

    uintn_t                         numberOfTableEntries;
    EFIConfigurationTable           *configurationTable;
} EFISystemTable;


#ifdef __cplusplus
}
#endif
 
#endif //!__UEFI_H__

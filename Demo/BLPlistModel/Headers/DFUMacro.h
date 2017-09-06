//
//  DFUMacro.h
//  iHealthSDKStatic
//
//  Created by Lei Bao on 2017/7/18.
//  Copyright © 2017年 daiqingquan. All rights reserved.
//

#ifndef DFUMacro_h
#define DFUMacro_h

@class DFUDeviceFirmwareInfo;
@class DFUServerFirmwareInfo;

typedef NS_ENUM(NSInteger, DFUError) {
    DFUError_UnsupportedDeviceType = 100, //Device type does not support.
    DFUError_InvalidUUID = 101, // UUID is invalid.
    DFUError_CommandTimeOut = 102, //Query device firmware information command timeout.
    DFUError_NoConnectedDevice = 104, //Device is not connected.
    DFUError_InUpgradeCannotExecuteCommand = 105, // During DFU, other commands cannot be executed.
    DFUError_InvalidFirmwareVersion = 106, // Firmware version is invalid.
    DFUError_InvalidHardwareVersion = 107, // Hardware version is invalid.
    DFUError_InvalidFirmwareInfoFile = 108, // The firmware info file is wrong.
    DFUError_InvalidFirmwareFile = 109, // The firmware file is wrong.
    DFUError_NetworkError = 200, // It indicates network error.
    DFUError_ServerError = 202, // Server error
    DFUError_RequestedFileNotExist = 203, // Requested file does not exist.
    DFUError_FileSaveError = 204, // File save error
    DFUError_InfoFileCheckNotPass = 205, // Info file does not pass check.
    DFUError_firmwareFileCheckNotPass = 206, // Firmware file does not pass check.
    DFUError_DeviceDisconnect = 300, // Device disconnects before command finish.
    DFUError_DeviceStopUpdate = 301, // Device stops update.
    DFUError_NoFirmwareFile = 402, // The firmware file does not exist.
    DFUError_DeleteError = 407, // Delete error
    DFUError_DeleteWhileFileNotExist = 408, // Delete file , but file does not exist
    
};

// Enum
typedef NS_ENUM(NSInteger, DFUDeviceType) {
    DFUDeviceType_Unknown = -1,
    DFUDeviceType_AM3,
    DFUDeviceType_AM3S,
    DFUDeviceType_AM4,
    DFUDeviceType_PO3,
    DFUDeviceType_HS2,
    DFUDeviceType_HS4,
    DFUDeviceType_ECG,
    DFUDeviceType_BP5S,
    DFUDeviceType_ABPM,
    DFUDeviceType_BG5S,
    DFUDeviceType_MAX,
};

typedef NS_ENUM(NSInteger, DFUDeviceReplyCannotUpgradeReason){
    DFUDeviceReplyCannotUpgradeReason_Unknown = 1,
    DFUDeviceReplyCannotUpgradeReason_Battery, // battery is low
    DFUDeviceReplyCannotUpgradeReason_InMeasuring, // cannot upgrade when measuring
};

typedef NS_ENUM(NSInteger, DFUUpgradeFailReason) {
    DFUUpgradeFailReason_Unknown = -1,
    DFUUpgradeFailReason_DeviceRecieveWrongDataOrNotRecieve,
    DFUUpgradeFailReason_WriteMCUError,
    DFUUpgradeFailReason_DeviceStopUpgrade,
};

typedef NS_ENUM(NSInteger, DFUTransmissionResultType) {
    DFUTransmissionResultType_Unknown = -1,
    DFUTransmissionResultType_Finish, // All firmware transfer finish
    DFUTransmissionResultType_Pause, // Pasuse because device needs write MCU
};

typedef NS_ENUM(NSInteger, DFUPauseReason) {
    DFUPauseReason_Unknown = 0, // unkonw reason
    DFUPauseReason_RebootAndNeedReconnect, // need write MCU, if finished, device can be connected.
};

typedef NS_ENUM(NSInteger, DFUState) {
    DFUState_Unknown = -1, 
    DFUState_Busy,
    DFUState_Free,
};



// Block
typedef void (^DFUErrorBlock)(DFUError error);

typedef void (^QueryDeviceFirmwareInfoSuccessBlock)(DFUDeviceFirmwareInfo *deviceFirmwareInfo);

typedef void (^QueryServerFirmwareInfoSuccessBlock)(DFUServerFirmwareInfo *serverFirmwareInfo);

typedef void (^DownloadFirmwareSuccessBlock)(NSString *firmwareIdentifier);
typedef void (^DownloadFirmwareStartBlock)();
typedef void (^DownloadFirmwareProgressBlock)(NSInteger progress);

typedef void (^CancelDownloadFirmwareSuccessBlock)();

typedef void(^DeviceReplyCannotUpgradeBlock)(DFUDeviceReplyCannotUpgradeReason reason);

typedef void(^TransferBeginBlock)();
typedef void(^TransferProgressBlock)(NSInteger progress);
typedef void(^TransferSuccessBlock)(NSUInteger writeMCUSpeed);
typedef void(^TransferResultBlock)(DFUTransmissionResultType type,DFUPauseReason reason,NSInteger pauseLength);

typedef void(^UpgradeSuccessBlock)();
typedef void(^UpgradeFailBlock)(DFUUpgradeFailReason reason);

typedef void(^StopUpgradeSuccessBlock)();

typedef void(^DeleteFirmwareSuccessBlock)();

#endif /* DFUMacro_h */

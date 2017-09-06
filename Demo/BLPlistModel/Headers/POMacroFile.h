//
//  POMacroFile.h
//  POSDK
//
//  Created by 小翼 on 14-8-11.
//  Copyright (c) 2014年 hejiasu. All rights reserved.
//

#import "HealthUser.h"

#ifndef POSDK_POMacroFile_h
#define POSDK_POMacroFile_h

#define PO3DeviceID @"ID"
#define PO3SDKRightApi  @"OpenApiSpO2"

#define PO3Discover       @"PO3Discover"
#define PO3ConnectFailed   @"PO3ConnectFailed"
#define PO3ConnectNoti @"PO3ConnectNoti"
#define PO3DisConnectNoti @"PO3DisConnectNoti"

typedef enum{
    PO3Error_OverTime  = 0,  // Bluetooth Communication Error
    PO3Error_ResetDeviceFaild,     // Send failed
    PO3Error_Disconnect,      // Device is disconnected
    PO3Error_ParameterError = 400,   //ParameterError
    PO3Error_FirmwareVersionIsNotSupported //firmware version is not supported
}PO3ErrorID;



typedef void (^DisposePO3ErrorBlock)(PO3ErrorID errorID);

typedef void (^DisposePO3SyncTimeBlock)(BOOL resetSuc);

typedef void (^DisposePO3StartMeasure)(BOOL resetSuc);
typedef void (^DisposePO3MeasureData)(NSDictionary *measureDataDic);
typedef void (^DisposePO3FinishMeasure)(BOOL finishData);

typedef void (^DisposePO3OfflineDataCount)(NSNumber* dataCount);
typedef void (^DisposePO3OfflineData)(NSDictionary *OfflineData);
typedef void (^DisposePO3OfflineWaveData)(NSDictionary *offlineWaveDataDic);
typedef void (^DisposePO3FinishUpload)(BOOL resetSuc);

typedef void (^DisposePO3ResetDeviceBlock)(BOOL resetSuc);

typedef void (^DisposePO3BatteryBlock)(NSNumber *battery);

typedef void (^DisposePO3DisconnectBlock)(BOOL resetSuc);



typedef void (^DisposeSendPO3DataBlock)();

#endif

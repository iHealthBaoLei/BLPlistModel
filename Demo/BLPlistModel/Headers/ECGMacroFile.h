//
//  ECGMacroFile.h
//  iHealthDemoCode
//
//  Created by zhiwei jing on 16/7/12.
//  Copyright © 2016年 zhiwei jing. All rights reserved.
//

#import "HealthUser.h"

#ifndef ECGMacroFile_h
#define ECGMacroFile_h


#define ECGUSBConnectNoti @"ECGUSBConnect"
#define ECGUSBDisConnectNoti @"ECGUSBDisConnectNoti"
#define ECGSDKECGRightApi  @"OpenApiECG"
#define ECG3Discover         @"ECG3Discover"
#define ECG3ConnectFailed    @"ECG3ConnectFailed"
#define ECG3ConnectNoti @"ECG3ConnectNoti"
#define ECG3DisConnectNoti @"ECG3DisConnectNoti"
#define ECG3DeviceID @"ID"

typedef enum{
    ECGUSBDataTransmissionTag_Restore = 0,
    ECGUSBDataTransmissionTag_Pause
}ECGUSBDataTransmissionTag;

typedef enum{
    ECG3Error_ElectrodeLoss = 1,        
    ECG3Error_ElectrodeLossRecovery,    
    ECG3Error_ElectrodeLossTimeout,     
    ECG3Error_SDCardCommunicationError, 
    ECG3Error_CollectionModuleError,    
    ECG3Error_LowPower,                 
    ECG3Error_DeviceMemoryFull,         
    ECG3Error_Disconnect,               
    ECG3Error_OverTime,                 
   
    ECG3Error_DeleteError,
    ECG3Error_ErrorData,
    ECG3Error_NoData,
    ECG3Error_ResetSDCardError,

    ECG3Error_ParameterError = 400,
    ECG3Error_UserInvalidateRight,             
    ECG3Error_FirmwareVersionIsNotSupported    

}ECG3ErrorID;



typedef void (^DisposeECG3SyncTimeBlock)(BOOL resetSuc); //Sync Time
typedef void (^DisposeECG3ErrorBlock)(ECG3ErrorID errorID); //Communication error codes, see ECG3 error descriptions.
typedef void (^DisposeECG3StartMeasureBlock)(BOOL resetSuc); //Start Measure
typedef void (^DisposeECG3MeasureDataBlock)(NSArray* measureDataArray);//Measure Data
typedef void (^DisposeECG3FinishMeasureBlock)(BOOL resetSuc);//Finish Measure
typedef void (^DisposeECG3GetBatteryBlock)(NSNumber *battery);//Battery


typedef void (^DisposeECG3DataStartSyncBlock)();
typedef void (^DisposeECG3DataInfo)(NSDictionary *infoDic);
typedef void (^DisposeECG3DataFinishSyncBlock)();
typedef void (^DisposeECG3DataSyncProgressBlock)(NSNumber *dataProgress);

typedef void (^DisposeECG3DeleteAllDataSuccessBlock)();



#endif /* ECGMacroFile_h */

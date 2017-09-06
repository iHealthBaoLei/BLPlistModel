//
//  HSMacroFile.h
//  HSDemoCode
//
//  Created by zhiwei jing on 14-7-23.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import "HealthUser.h"

#ifndef HSDemoCode_HSMacroFile_h
#define HSDemoCode_HSMacroFile_h

#define RecordLength 16
//HS2
typedef enum{
    HS2DeviceLowPower = 1, // Battery level is low 1
    HS2DeviceEr0, // The Scale failed to initialize 2
    HS2DeviceEr1, // Maximum weight has been exceeded 3
    HS2DeviceEr2, // The Scale can't capture a steady reading 4
    HS2DeviceEr4, // Bluetooth connection error 5
    HS2DeviceEr7, // Movement while measuring 6
    HS2DeviceEr8, //Invalidate  7
    HS2DeviceEr9, // Scale memory access error  8
    HS2DataZeor, // No memory  9
    HS2DeviceDisconnect, //Device disconnect 10
    HS2DeviceSendTimeout, // Communication error 11
    HS2DeviceRecWeightError, //
    HS2UserInvalidate = 400//User verify error
}HS2DeviceError;

//HS3 error
typedef enum{
    HS3DeviceLowPower = 1, //Low battery
    HS3DeviceEr2, //Weight capacity is exceeded
    HS3DeviceEr4, //The Scale calibration error
    HS3DeviceEr7, //Movement while measuring
    HS3DataZeor, //No memory
    HS3DeviceDisconnect, //Device disconnect
    HS3DeviceSendTimeout, //Communication error
    HS3UserInvalidate = 400//User verify error
}HS3DeviceError;

//HS4 error
typedef enum{
    HS4DeviceLowPower = 1, // Battery level is low
    HS4DeviceEr0, // The Scale failed to initialize
    HS4DeviceEr1, // Maximum weight has been exceeded
    HS4DeviceEr2, // The Scale can't capture a steady reading
    HS4DeviceEr4, // Bluetooth connection error
    HS4DeviceEr7, // Movement while measuring
    HS4DeviceEr8, //Invalidate
    HS4DeviceEr9, // Scale memory access error
    HS4DataZeor, // No memory
    HS4DeviceDisconnect, //Device disconnect
    HS4DeviceSendTimeout, // Communication error
    HS4DeviceRecWeightError, //
    HS4UserInvalidate = 400//User verify error
}HS4DeviceError;

//HS5 error
typedef enum{
    IHSCOverTimeError = 0,   // Communication error
    IHSCUserInScale=5,  // Communication Error
    IHSCLowPower=6, // Make sure batteries are installed correctly, if the problem persists, replace with a new set of batteries.
    IHSCScaleEr0=7,  // Remove the batteries, wait 1 minute and then replace with a new set of batteries.
    IHSCScaleEr1=8, // The current weight may be beyond the measurement range of 330 lbs/150 kg.
    IHSCScaleEr2=9, // Stand still on all four electrodes with bare feet.
    IHSCScaleEr7=10,  // Communication Error
    IHSCScaleEr8=11,  // Communication Error
    IHSCScaleEr9=12,  // Communication Error
    IHScaleBusy=13,// Scale is busy
    HS5DataZeor=14,// No memory
    IHSCScaleCreateUserTestError,
    HS5Disconnect, //Device disconnect
    HS5UserInvalidate = 400//User verify error
    
}HS5DeviceError;

//HS6 Unit
typedef enum{
    IHHS6SDKUnitWeight_kg = 0,  //
    IHHS6SDKUnitWeight_lbs,     //
    IHHS6SDKUnitWeight_oz,     //
} IHHS6SDKUnitWeight;           //WeightUnit

#pragma mark HS2  Block
typedef void (^DisposeHS2Result)(BOOL resetSuc);
//HS4 error
typedef void (^DisposeHS2ErrorBlock)(HS2DeviceError errorID);

//Start Memory transmission
typedef void (^StartHS2Transmission)(NSDictionary *startDataDictionary);
//Memory transmission progress，0.0～1.0.
typedef void (^DisposeHS2Progress)(NSNumber *progress);
//data including weight (kg), measurement time，coordinated key：weight，date.
typedef void (^HS2MemorryData)(NSArray *historyDataArray);
//Finish memory transmission.
typedef void (^FinishHS2Transmission)();
//Current weight, (Kg)
typedef void (^HS2UnStableWeight)(NSNumber *unStableWeight);
//Stable weight, (Kg)
typedef void (^HS2StableWeight)(NSDictionary *StableWeightDic);

typedef void (^DisposeSendHS2DataBlock)();



typedef void (^DisposeHS2BatteryBlock)(NSNumber *battary);


#pragma mark HS3  Block
//deviceID
typedef void(^WeightID)(NSString *weightID);
//HS3Error
typedef void (^DisposeHS3ErrorBlock)(HS3DeviceError errorID);
//Memory Number，0～200.
typedef void (^DisposeHS3UploadDataNum)(NSNumber *uploadDataNum);
//Memory transmission progress，0.0～1.0.
typedef void (^DisposeHS3Progress)(float progress);
//Record data including weight(kg), measure time，coordinated key：weight、date.
typedef void (^HS3MemorryData)(NSDictionary *historyDataDic);
//Start transmission
typedef void (^StartHS3Transmission)(BOOL startTransmission);
//Finish memory transmission.
typedef void (^FinishHS3Transmission)();
//Stable weight (Kg)
typedef void (^StableHS3Weight)(NSDictionary *StableWeightDic);
//
typedef void (^FinishHS3Init)();
//
typedef void (^DisposeResult)(BOOL resetSuc);


#pragma mark HS4  Block
typedef void (^DisposeResult)(BOOL resetSuc);
//HS4 error
typedef void (^DisposeHS4ErrorBlock)(HS4DeviceError errorID);

//Start Memory transmission
typedef void (^StartHS4Transmission)(NSDictionary *startDataDictionary);
//Memory transmission progress，0.0～1.0.
typedef void (^DisposeProgress)(NSNumber *progress);
//data including weight (kg), measurement time，coordinated key：weight，date.
typedef void (^MemorryData)(NSArray *historyDataArray);
//Finish memory transmission.
typedef void (^FinishHS4Transmission)();
//Current weight, (Kg)
typedef void (^UnStableWeight)(NSNumber *unStableWeight);
//Stable weight, (Kg)
typedef void (^StableWeight)(NSDictionary *StableWeightDic);

typedef void (^DisposeSendHS4DataBlock)();


#pragma mark HS5  Block
//Existing user info in HS5，including serialNub、Position of users. Related key: serialNumber、position
typedef void (^MemorryUserListHS5Data)(NSArray *userListDataArray);
//HS5 result
typedef void (^DisposeHS5Result)(BOOL resetSuc);
//HS5 error
typedef void (^DisposeHS5ErrorBlock)(HS5DeviceError errorID);
//Start memory transmission.
typedef void (^StartHS5Transmission)(BOOL startHS5Transmission);
//progress: Memory transmission progress，0.0～1.0.
typedef void (^DisposeHS5Progress)(NSNumber *progress);
// Record data，More details and key refer Measure API. Additionally add time-measure property, related key: date.
typedef void (^MemorryHS5Data)(NSDictionary *historyDataDic);
//Finish Memory Transmission
typedef void (^FinishHS5Transmission)(BOOL finishHS5Transmission);
//Current weight, (kg)
typedef void (^UnStableHS5Weight)(NSNumber *unStableWeight);
//Stable weight, (kg)
typedef void (^StableHS5Weight)(NSNumber *StableWeight);
//Weight by impedence, (kg)
typedef void (^ImpedanceWeight)(NSNumber*ImpedanceWeight);
//body info, includes weight(kg), fat content(%), water content(%), muscle content(%), bone mass, visceral fat level, DCI(Kcal). keys: weight, weightFatValue, waterValue, muscleValue, skeletonValue, VFatLevelValue, DCIValue
typedef void (^BodyCompositionMeasurements)(NSDictionary*BodyCompositionInforDic);
//
typedef void (^GetScaleSuperPassword)(NSString*superPassword);
//CurrentSerialNub
typedef void (^CurrentSerialNub)(NSInteger serialNub);

typedef void (^DisposeSendHS5DataBlock)();


#pragma mark HS6  Block
typedef void (^DisposeHS6SuccessBlock)(NSDictionary* deviceInfo);

typedef void (^DisposeHS6FailBlock)(NSString* failmsg);

typedef void (^DisposeHS6EndBlock)(NSDictionary* deviceDic);

typedef void (^DisposeHS6ErrorBlock)(NSNumber* error);

//Binding QR Device
typedef void(^BinedQRDeviceBlock)(NSArray *resultArray);
//Binding QR Device
typedef void(^BinedQRDeviceErrorBlock)(NSString *errorCode);

//unbind Device
typedef void(^DisBinedQRDeviceBlock)(NSArray *resultArray);
//unbind QR Device
typedef void(^DisBinedQRDeviceErrorBlock)(NSString *errorCode);

//typedef void (^BlockHS6UserAuthentication)(UserAuthenResult result);


typedef void (^DisposeHS6GetOpenAPISuccessBlock)(NSDictionary* openAPIInfoDic);
typedef void (^DisposeHS6GetOpenAPIErrorBlock)(NSDictionary *errorCode);

typedef void (^DisposeHS6SyncWeightUnitSuccessBlock)(BOOL syncWeightUnit);
typedef void (^DisposeHS6SyncWeightUnitErrorBlock)(NSString *errorCode);



typedef void (^BlockUserAuthentication)(UserAuthenResult result);//the result of userID verification
typedef void (^BlockDataFromCloud)(NSArray *dataArray);//the result of userID verification


#define HS3ConnectNoti @"HS3ConnectNoti"
#define HS3DisConnectNoti @"HS3DisConnectNoti"

#define HS2Discover        @"HS2Discover"
#define HS2ConnectFailed   @"HS2ConnectFailed"
#define HS2ConnectNoti    @"HS2ConnectNoti"
#define HS2DisConnectNoti @"HS2DisConnectNoti"

#define HS4Discover        @"HS4Discover"
#define HS4ConnectFailed   @"HS4ConnectFailed"
#define HS4ConnectNoti    @"HS4ConnectNoti"
#define HS4DisConnectNoti @"HS4DisConnectNoti"


#define HS5ConnectNoti @"HS5ConnectNoti"
#define HS5DisConnectNoti @"HS5DisConnectNoti"

#define HSDeviceID @"ID"
#define HSSDKRightApi  @"OpenApiWeight"


#define ContinuaHSDiscover        @"ContinuaHSDiscover"
#define ContinuaHSConnectFailed   @"ContinuaHSConnectFailed"
#define ContinuaHSConnectNoti @"ContinuaHSConnectNoti"
#define ContinuaHSDisConnectNoti @"ContinuaHSDisConnectNoti"


#endif

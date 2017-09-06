//
//  BGMacroFile.h
//  BGDemoCode
//
//  Created by zhiwei jing on 14-6-29.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import "HealthUser.h"
#import "BGDevice.h"
#import "BGController.h"
@class BG5SStateInfo;
@class BG5SRecordModel;

#ifndef BGDemoCode_BGMacroFile_h
#define BGDemoCode_BGMacroFile_h

typedef enum {
    BGOpenMode_Strip = 1,//BGOpenMode_Strip means booting the meter by insert the strip
    BGOpenMode_Hand//BGOpenMode_Hand means booting the meter by pressing the on/off button.
}BGOpenMode;

typedef enum {
    BGMeasureMode_Blood = 1,//BGMeasureMode_Blood means blood measurement mode
    BGMeasureMode_NoBlood//BGMeasureMode_NoBlood means control solution measurement mode.
}BGMeasureMode;

typedef enum {
    BGCodeMode_GOD = 1,//BGCodeMode_GOD means GOD blood test strip.
    BGCodeMode_GDH//BGCodeMode_GDH means GDH Blood test strip.
}BGCodeMode;

typedef enum {
    BGUnit_mmolPL = 1,//BGUnit_mmolPL stands for mmol/L
    BGUnit_mgPmL//BGUnit_mgPmL stands for mg/dL
}BGUnit;


/**
 * BG1 errorID:
 * 00：Battery is low.
 * 01：Glucose test result is out of the measurement range.
 * 02：2.5V reference voltage error, not normal measurement, please repeat the test.
 * 03：Strip is used or unknown moisture detected, discard the test strip and repeat the test with a new strip.
 * 04：CODE value check error. This error need let user scan code and call the send code function again,no alert need to show.
 * 05\06：The environmental temperature is beyond normal range, place the meter at room temperature for at least 30 minutes, then repeat the test.
 * 07：Authentication failed more than 10 times.
 * 08：Packet loss in the process of sending CODE.
 * 09：Tooling inspection process is not completed.
 * 10: Encryption burn write bit is empty.
 * 11: Compulsory Authentication is not passed.
 * 12: Glucose test result is low.
 * 13: Glucose test result is high.
 
 * 300: BG unknown.
 * 301: BG time out.
 * 330: BG sleeping mode.
 * 331: hand shake failed.
 * 400: Parameter input error.
 */

typedef enum{
    BG1Error_LowBattery = 0,
    BG1Error_ResultOutOfMeasurementRage = 1,
    BG1Error_UnvalidReferenceVoltage = 2,
    BG1Error_StripUsed = 3,
    BG1Error_CodeError = 4,
    BG1Error_RoomTemperatureOutOfRange1 = 5,
    BG1Error_RoomTemperatureOutOfRange2 = 6,
    BG1Error_AuthenticationFailed = 7,
    BG1Error_CodeSendLost = 8,
    BG1Error_ToolingTestFailed = 9,
    BG1Error_EncryptionFailed = 10,
    BG1Error_CompulsoryAuthenticationFaild = 11,
    BG1Error_ResultLow = 12,
    BG1Error_ResultHigh = 13,
    
    BG1Error_Unknown = 300,
    BG1Error_TimeOut = 301,
    BG1Error_DisConnented = 303,
    BG1Error_SleepingMode =330,
    BG1Error_HandShakeFailed = 331,
    BG1Error_ParameterError = 400,
}BG1Error;


//UI
#define kNotificationNameNeedAudioPermission @"LetkNotificationNameNeedAudioPermission"
#define kNotificationNameAudioDeviceInsert @"kNotificationNameAudioDeviceInsert"
#define kNotificationNameBG1DidDisConnect @"kNotificationNameBG1DidDisConnect"


typedef void (^DisposeBG1DiscoverBlock)();
typedef void (^DisposeBG1IDPSBlock)(NSDictionary* idpsDic);
typedef void (^DisposeBG1ConnectBlock)();
typedef void (^DisposeBG1ErrorBlock)(BG1Error errorID);
typedef void (^DisposeBG1SendCodeResultBlock)();

//
typedef void (^DisposeBGStripInBlock)();
//
typedef void (^DisposeBGStripOutBlock)();
//
typedef void (^DisposeBGBloodBlock)();
//
typedef void (^DisposeBGResultBlock)(NSDictionary* result);
//
typedef void (^DisposeBGSendCodeBlock)(BOOL sendOk);
//
typedef void (^DisposeBGErrorBlock)(NSNumber* errorID);
//
typedef void (^DisposeBG5KeepConnectBlock)(BOOL sendOk);
//
typedef void (^DisposeBGSetTime)(BOOL setResult);
//
typedef void (^DisposeBGSetUnit)(BOOL setResult);
//
typedef void (^DisposeBGBottleID)(NSNumber *bottleID);
//
typedef void (^DisposeBGDataCount)(NSNumber* dataCount);
//
typedef void (^DisposeBGHistoryData)(NSDictionary *historyDataDic);
//
typedef void (^DisposeBGDeleteData)(BOOL deleteOk);
//
typedef void(^DisposeBGSendBottleIDBlock)(BOOL sendOk);
//
typedef void (^DisposeBGCodeDic)(NSDictionary *codeDic);
//
typedef void (^DisposeBGSendCodeBlock)(BOOL sendOk);
//
typedef void (^DisposeBGStartModel)(BGOpenMode mode);
//
typedef void (^DisposeBGBatteryBlock)(NSNumber* energy);


#define kNotificationNameBG3ConnectSuccess @"kNotificationNameBG3ConnectSuccess"
#define kNotificationNameBG3DidDisConnect @"kNotificationNameBG3DidDisConnect"


// ------ BG5 Baolei ------
#define BG5ConnectNoti @"BG5ConnectNoti"
#define BG5DisConnectNoti @"BG5DisConnectNoti"

/**
 BG5Error

 - BG5Error_Unknown: Unknown error
 - BG5Error_LowBattery: Battery is low.
 - BG5Error_ResultOutOfMeasurementRage: Glucose test result is out of the measurement range.
 - BG5Error_UnvalidReferenceVoltage: 2.5V reference voltage error, not normal measurement, please repeat the test.
 - BG5Error_StripUsed: Strip is used or unknown moisture detected, discard the test strip and repeat the test with a new strip.
 - BG5Error_ErrorOccurInEEPROM: Reading transmission error. Repeat the test with a new test strip. If the problem persists, contact iHealth customer service for assistance.
 - BG5Error_RoomTemperatureOutOfRange1: The environmental temperature is beyond normal range, place the meter at room temperature for at least 30 minutes, then repeat the test.
 - BG5Error_RoomTemperatureOutOfRange2: The environmental temperature is beyond normal range, place the meter at room temperature for at least 30 minutes, then repeat the test.
 - BG5Error_TestStripCodingError1: Test strip coding error.
 - BG5Error_TestStripCodingError2: Test strip coding error.
 - BG5Error_PullOffStripWhenMeasuring: Strip removed in the middle of reading, repeat the test with a new strip.
 - BG5Error_ShouldPullOffStripAfterReadingResult: Pull off strips after measuring
 - BG5Error_CannotWriteSNOrKey: SN or KEY write error
 - BG5Error_NeedSetTime: Please set time.
 - BG5Error_StripNumberIsZero: 0 test strips remaining.
 - BG5Error_StripExpired: Test strip expired.
 - BG5Error_CannotMeasureWhenCharging: Unplug the charging cable before testing.
 - BG5Error_InputParametersError: Parameter input error.
 - BG5Error_FunctionCallOrderError: Fucntion call order error
 - BG5Error_MeasureModeNotMatch: Measure mode is not match.
 - BG5Error_CommandTimeout: Command timeout
 - BG5Error_CommandNotSupport: Command is not supported for current device.
 */
typedef NS_ENUM(NSInteger, BG5Error) {
    BG5Error_Unknown = -1,
    BG5Error_LowBattery = 0,
    BG5Error_ResultOutOfMeasurementRage = 1,
    BG5Error_UnvalidReferenceVoltage = 2,
    BG5Error_StripUsed = 3,
    BG5Error_ErrorOccurInEEPROM = 4,
    BG5Error_RoomTemperatureOutOfRange1 = 5,
    BG5Error_RoomTemperatureOutOfRange2 = 6,
    BG5Error_TestStripCodingError1 = 7,
    BG5Error_TestStripCodingError2 = 8,
    BG5Error_PullOffStripWhenMeasuring = 9,
    BG5Error_ShouldPullOffStripAfterReadingResult = 10,
    BG5Error_CannotWriteSNOrKey = 11,
    BG5Error_NeedSetTime = 12,
    BG5Error_StripNumberIsZero = 13,
    BG5Error_StripExpired = 14,
    BG5Error_CannotMeasureWhenCharging = 15,
    BG5Error_InputParametersError = 400,
    BG5Error_FunctionCallOrderError = 402,
    BG5Error_MeasureModeNotMatch = 403,
    BG5Error_CommandTimeout = 500,
    BG5Error_CommandNotSupport = 501,
};

// ------ BG5S Baolei ------

#define kNotificationNameBG5SDidDiscover        @"BG5SDiscover"
#define kNotificationNameBG5SConnectFail        @"BG5SConnectFailed"
#define kNotificationNameBG5SConnectSuccess     @"BG5SConnectNoti"
#define kNotificationNameBG5SDidDisConnect      @"BG5SDisConnectNoti"

// --------------- ENUMERATION ---------------
typedef NS_ENUM(NSInteger, BG5SCommandAction) {
    BG5SCommandAction_Unknown = -1,
    BG5SCommandAction_QueryBG5SStateInfo,
    BG5SCommandAction_SetBG5STime,
    BG5SCommandAction_SetBG5SUnit,
    BG5SCommandAction_SendBG5SCode,
    BG5SCommandAction_DeleteBG5SStripUsedInfo,
    BG5SCommandAction_QueryBG5SRecord,
    BG5SCommandAction_DeleteBG5SRecord,
    BG5SCommandAction_StartBG5SMeasure,
    //
    BG5SCommandAction_ErrorCode,
    BG5SCommandAction_StripInsert,
    BG5SCommandAction_StripPullOff,
    BG5SCommandAction_DropBlood,
    BG5SCommandAction_Result,
    BG5SCommandAction_EnterChagre,
    BG5SCommandAction_ExitCharge,
    
};

typedef NS_ENUM(NSInteger, BG5SError) {
    BG5SError_Unknown = -1,
    BG5SError_LowBattery = 0,
    BG5SError_PullOffStripWhenMeasuring = 1,
    BG5SError_UnvalidReferenceVoltage = 2,
    BG5SError_StripUsed = 3,
    BG5SError_ErrorOccurInEEPROM = 4,   // No code info in BG5S itself
    BG5SError_LowTemperature = 5,
    BG5SError_HighTemperature = 6,
    BG5SError_BluetoothError = 7,       // only showed in BG5's screen
    BG5SError_ResultLow = 8,            // result out of range
    BG5SError_ResultHigh = 9,           // result out of range
    BG5SError_FactoryError = 10,
    BG5SError_InputParametersError = 400,
    BG5SError_RecordTotalNumberNotMatchTransferTotalNumber = 401,
    BG5SError_CommandTimeout = 500,
    BG5SError_CommandNotSupport = 501,
};

typedef NS_ENUM(NSInteger, BG5SStripState) {
    BG5SStripState_Unknown = -1,
    BG5SStripState_Insert,
    BG5SStripState_PullOff,
};

typedef NS_ENUM(NSInteger, BG5SChargeState) {
    BG5SChargeState_Unknown = -1,
    BG5SChargeState_Charging,
    BG5SChargeState_ExitCharge,
};

typedef void(^BG5SStateInfoBlock)(BG5SStateInfo *stateInfo);
typedef void(^BG5SRecordBlock)(NSArray *array);
/**
 Block without return parameters
 */
typedef void(^BG5SSuccessBlock)();

/**
 Block show the result of setting code
 
 @param success YES:success NO:fail
 */
typedef void(^BG5SSetCodeResultBlock)(BOOL success);


//typedef void(^BG5SRecordBlock)(NSArray *array);

/**
 Error block with error type
 
 @param error error type
 */
typedef void(^BG5SSDKErrorBlock)(BG5SError error,NSString *detailInfo);

#endif

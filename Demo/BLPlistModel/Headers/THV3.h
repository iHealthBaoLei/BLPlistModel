//
//  THV3.h
//  iHealthDemoCode
//
//  Created by Realank on 2016/12/23.
//  Copyright © 2016年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, THV3RcvDataType) {
    THV3RcvDataRT,
    THV3RcvDataButtonStatus,
};

typedef NS_ENUM(NSUInteger, THV3RcvButtonType) {
    THV3RcvBtnNone,
    THV3RcvBtnPower,
    THV3RcvBtnAudio,
    THV3RcvBtnMemory,
    THV3RcvBtnCF
    
};

typedef enum : NSUInteger {
    THV3StatusUnInit,
    THV3StatusInitTime,
    THV3StatusInitConfig,
    THV3StatusWorking,
} THV3Status;



@interface THV3HistoryData : NSObject 
@property (nonatomic, strong) NSDate* measureDate;
@property (nonatomic, assign) float temperature;
@property (nonatomic, assign) BOOL isHumanBody;
@end

typedef void(^ReceiveHistoryBlock)(NSArray<THV3HistoryData*>* dataArray);
typedef void(^ConfigResultBlock)(BOOL success);

@interface THV3 : NSObject

@property (nonatomic, assign) THV3Status status;//status to flag whether device is ready
@property (strong, nonatomic) NSString *name;
@property (strong, nonatomic) NSString *currentUUID;
//‘serialNumber’ is for separating different device when multiple device have been connected.
@property (strong, nonatomic) NSString *serialNumber;//MAC
@property (strong, nonatomic) NSTimer *firmwareVersion;

@property (nonatomic, assign) THV3RcvDataType rtDataType;
@property (nonatomic, strong) THV3HistoryData* rtTemperature;// for temperature
@property (nonatomic, assign) BOOL voltIsNormal;// for battary
@property (nonatomic, assign) THV3RcvButtonType buttonType;//for button use
@property (nonatomic, assign) BOOL isButtonOn;//for button use

//status
@property (nonatomic, assign) NSInteger idleTimeInterval;
@property (nonatomic, assign) BOOL isUnitCelsius;
@property (nonatomic, assign) BOOL isTargetHuman;
@property (nonatomic, assign) BOOL isOfflineMode;

- (void)readHistoryDataWithResultBlock:(ReceiveHistoryBlock)receivedDataBlock;

- (void)configIdleTime:(NSUInteger)timeInterval withResultBlock:(ConfigResultBlock)resultBlock;
- (void)configTemperUnit:(BOOL)isCelsius withResultBlock:(ConfigResultBlock)resultBlock;
- (void)configMeasureTarget:(BOOL)isHumanBody withResultBlock:(ConfigResultBlock)resultBlock;
- (void)configOfflineMode:(BOOL)isOffline withResultBlock:(ConfigResultBlock)resultBlock;
- (void)commandDisconnectDevice;
@end

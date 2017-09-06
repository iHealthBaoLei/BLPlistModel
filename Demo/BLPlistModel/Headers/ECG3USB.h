//
//  ECG3.h
//  iHealthDemoCode
//
//  Created by daiqingquan on 15/9/15.
//  Copyright (c) 2015年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ECGMacroFile.h"

@interface ECG3USB : NSObject
@property (strong, nonatomic) NSString *currentUUID;
@property (strong, nonatomic) NSString *serialNumber;
@property (strong, nonatomic) NSString *firmwareVersion;





-(void)commandECG3SyncDataStart:(DisposeECG3DataStartSyncBlock)startSync withDataInfo:(DisposeECG3DataInfo)dataInfo withFinishSync:(DisposeECG3DataFinishSyncBlock)finishSync withSyncProgress:(DisposeECG3DataSyncProgressBlock)syncProgress withErrorBlock:(DisposeECG3ErrorBlock)errorBlock;


-(void)commandECG3DeleteAllData:(DisposeECG3DeleteAllDataSuccessBlock)deleteAllData withErrorBlock:(DisposeECG3ErrorBlock)errorBlock;


@end

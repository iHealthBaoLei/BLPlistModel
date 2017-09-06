//
//  ECG3Controller.h
//  iHealthDemoCode
//
//  Created by daiqingquan on 15/9/15.
//  Copyright (c) 2015年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ECG3USB;
@interface ECG3USBController : NSObject
+(ECG3USBController *)shareECG3USBController;
-(ECG3USB *)getAllCurrentECG3USBInstace;
@end

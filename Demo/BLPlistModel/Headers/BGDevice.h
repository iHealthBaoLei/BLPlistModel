//
//  BGDevice.h
//  iHealthDemoCode
//
//  Created by Realank on 2017/1/4.
//  Copyright © 2017年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BGDevice : NSObject

@property (strong, nonatomic) NSString *currentUUID;
///‘serialNumber’ is for separating different device when multiple device have been connected.
@property (strong, nonatomic) NSString *serialNumber;
@property (strong, nonatomic) NSString *firmwareVersion;

@end

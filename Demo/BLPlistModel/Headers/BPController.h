//
//  BPController.h
//  iHealthDemoCode
//
//  Created by Realank on 2017/1/4.
//  Copyright © 2017年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BPController : NSObject{
    //区分设备
    NSString* deviceName;
    //发送通知
    NSString* deviceConnectNotiName;
    NSString* deviceDisconnectNotiName;
    //创建实例
    Class DeviceClass;
}

-(instancetype) initUniqueInstance;

/**
 * Get all BP3 instance,Access control class instance after receiving BP3ConnectNoti, then use instance to call BP3 related communication methods.
 */
-(NSArray *)allConnectedInstance;

@end

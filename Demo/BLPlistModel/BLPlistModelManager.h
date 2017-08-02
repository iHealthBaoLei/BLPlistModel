//
//  BLPlistModelManager.h
//  iHealthDemoCode
//
//  Created by Lei Bao on 2017/5/18.
//  Copyright © 2017年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BLPlistModelManager : NSObject

+ (NSArray *)getAllInstanceFromPlistWithClassName:(NSString *)className;

@end

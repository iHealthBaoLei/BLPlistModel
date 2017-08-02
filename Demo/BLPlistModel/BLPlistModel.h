//
//  BLPlistModel.h
//  iHealthDemoCode
//
//  Created by Lei Bao on 2017/5/18.
//  Copyright © 2017年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BLPlistModel : NSObject

/**
 The identifier of plist file, Plist name = Class name + '_' + identifier
 such as ClassA_12345678.plist
 */
@property (copy, nonatomic) NSString *identifier;

/**
 Last updated time
 */
@property (strong, nonatomic) NSDate *ts;

/**
 Save Self to Plist

 @param completion block
 */
- (void)savePlistWithCompletion:(void(^)(BOOL successful))completion;

/**
 Remove Plist

 @param completion block
 */
- (void)removePlistWithCompletion:(void(^)(BOOL successful))completion;

@end

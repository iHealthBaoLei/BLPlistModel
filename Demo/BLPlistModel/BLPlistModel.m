//
//  BLPlistModel.m
//  iHealthDemoCode
//
//  Created by Lei Bao on 2017/5/18.
//  Copyright © 2017年 zhiwei jing. All rights reserved.
//

#import "BLPlistModel.h"
#import <objc/runtime.h>

@interface BLPlistModel()

@property (strong, nonatomic) NSString *plistName;
/**
 The path of plist file
 */
@property (copy, nonatomic) NSString *plistPath;

@end

@implementation BLPlistModel

- (void)savePlistWithCompletion:(void(^)(BOOL successful))completion{
    
    if (_identifier.length == 0) {
        NSException *e = [NSException exceptionWithName:@"Error property value: plistName can't be nil" reason:[NSString stringWithFormat:@"Class %@ plistName property is nil or length = 0",NSStringFromClass(self.class)] userInfo:nil];
        @throw e;
    }
    
    _plistName = [NSString stringWithFormat:@"%@_%@",NSStringFromClass([self class]),_identifier];
    NSLog(@"plist name: %@",_identifier);
    
    //
    [self configurePath];
    //
    NSMutableDictionary *dic_m = [NSMutableDictionary new];
    NSArray *properties = [[self allPropertys] allObjects];// 字符串数组，属性名称
    /* 循环的作用：把每个属性名当作Key，属性值当作Value，保存到Plist中;如果Value为nil，则不保存 */
    for (NSString *propertyName in properties) {
        NSArray *exProperties = @[@"plistName",@"plistPath"];
        if ([exProperties containsObject:propertyName]) {
            continue;
        }
        SEL propertyGetterSelector = NSSelectorFromString(propertyName);// 从属性名称得到Getter方法
        if ([self respondsToSelector:propertyGetterSelector]) {
            const char *returnType = [[self methodSignatureForSelector:propertyGetterSelector] methodReturnType]; // 得到返回值的类型
            /* 判断返回值类型，将属性的值转化成合法的值写入字典 */
            IMP imp = [self methodForSelector:propertyGetterSelector];
            id objectAsValue;
            if (strcmp(returnType, @encode(id)) == 0) {
                id (*func)(id,SEL) = (void *)imp;
                objectAsValue = func(self,propertyGetterSelector);
            } else if (strcmp(returnType, @encode(BOOL)) == 0) {
                BOOL (*func)(id, SEL) = (void *)imp;
                objectAsValue = @(func(self, propertyGetterSelector));
            } else if (strcmp(returnType, @encode(int)) == 0) {
                int (*func)(id, SEL) = (void *)imp;
                objectAsValue = @(func(self, propertyGetterSelector));
            } else if (strcmp(returnType, @encode(float)) == 0) {
                float (*func)(id, SEL) = (void *)imp;
                objectAsValue = @(func(self, propertyGetterSelector));
            } else if (strcmp(returnType, @encode(double)) == 0) {
                double (*func)(id, SEL) = (void *)imp;
                objectAsValue = @(func(self, propertyGetterSelector));
            }
            if (objectAsValue) {
                [dic_m setValue:objectAsValue forKey:propertyName];
            }
        }
        
        
        
    }
    
    //save to plist
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
        BOOL successFlag = NO;
#if TARGET_OS_IPHONE
        successFlag = [dic_m writeToFile:_plistPath atomically:YES];
#elif TARGET_OS_MAC
        NSData *data = [NSKeyedArchiver archivedDataWithRootObject:dictionary];
        successFlag = [[NSFileManager defaultManager]createFileAtPath:_plistPath contents:data attributes:nil];
#endif
        if (completion) {
            dispatch_async(dispatch_get_main_queue(), ^{
                completion(successFlag);
            });
        }
    });
}

- (void)removePlistWithCompletion:(void(^)(BOOL successful))completion{
    if (_identifier.length == 0) {
        NSException *e = [NSException exceptionWithName:@"Error property value: plistName can't be nil" reason:[NSString stringWithFormat:@"Class %@ plistName property is nil or length = 0",NSStringFromClass(self.class)] userInfo:nil];
        @throw e;
    }
    
    _plistName = [NSString stringWithFormat:@"%@_%@",NSStringFromClass([self class]),_identifier];
    NSLog(@"plist name: %@",_identifier);
    [self configurePath];
    NSError *error;
    [[NSFileManager defaultManager]removeItemAtPath:_plistPath error:&error];
    if (completion) {
        if (error) {
            completion(0);
        } else {
            completion(1);
        }
    }
    
}
#pragma mark - Internal Method
#pragma mark Configure Save Path
- (void)configurePath{
    NSString *path;
    NSString * appendedPlistName = [NSString stringWithFormat:@"%@.plist", _plistName];
    
    // Fetch out plist & set to new path
    NSArray *pathArray;
    NSString *documentsDirectory;
#if TARGET_OS_IPHONE
    pathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsDirectory = [pathArray objectAtIndex:0];
    path = [documentsDirectory stringByAppendingPathComponent:appendedPlistName];
#elif TARGET_OS_MAC
    NSString *name = [[NSBundle mainBundle] infoDictionary][(NSString *)kCFBundleNameKey];
    pathArray = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
    documentsDirectory = [pathArray objectAtIndex:0];
    NSString *directoryPath = [documentsDirectory stringByAppendingPathComponent:name];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL isDir = NO;
    if (![fileManager fileExistsAtPath:directoryPath isDirectory:&isDir]) {
        NSError *err;
        [fileManager createDirectoryAtPath:directoryPath withIntermediateDirectories:NO attributes:nil error:&err];
    }
    path = [directoryPath stringByAppendingPathComponent:appendedPlistName];
#endif
    _plistPath = path;
    NSLog(@"Path:%@",_plistPath);
}
#pragma mark Plist 2 Class
- (SEL) setterSelectorForPropertyName:(NSString *)propertyName {
    
    /*
     Because apple automatically generates setters to "setPropertyName:", we can use that and return the first argument to get the type of property it is.  That way, we can set it to our plist values.  Custom setters will cause problems.
     */
    
    // Make our first letter capitalized -  Using this because `capitalizedString` causes issues with camelCase => Camelcase
    NSString * capitalizedPropertyName = [propertyName stringByReplacingCharactersInRange:NSMakeRange(0,1) withString:[[propertyName substringToIndex:1] capitalizedString]];
    
    // The name of our auto synthesized setter | Custom setters will cause issues
    NSString * methodString = [NSString stringWithFormat:@"set%@:", capitalizedPropertyName];
    
    // Set our Selector
    SEL propertySetterSelector = NSSelectorFromString(methodString);
    
    // Return it
    return propertySetterSelector;
}
#pragma mark - 获得所有属性，包括子类和父类
- (NSSet *)allPropertys {
    NSMutableSet* result = [NSMutableSet new];
    Class observed = [self class];
    while ([observed isSubclassOfClass:[BLPlistModel class]]) {
        [self propertyForClass: observed withSet: &result];
        observed = [observed superclass];// 每次循环，都获得父类
    }
    return result;
}

- (void)propertyForClass: (Class)class withSet: (NSMutableSet **)result {
    unsigned int num_props;
    objc_property_t* prop_list;
    prop_list = class_copyPropertyList(class, &num_props);
    
    for(unsigned int i = 0; i < num_props; i++) {
        NSString * propName = [NSString stringWithUTF8String:property_getName(prop_list[i])];
        [*result addObject:propName];
    }
    free(prop_list);
}
@end

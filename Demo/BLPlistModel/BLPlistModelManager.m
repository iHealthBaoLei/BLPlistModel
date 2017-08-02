//
//  BLPlistModelManager.m
//  iHealthDemoCode
//
//  Created by Lei Bao on 2017/5/18.
//  Copyright © 2017年 zhiwei jing. All rights reserved.
//

#import "BLPlistModelManager.h"
#import "BLPlistModel.h"
#import <objc/runtime.h>

@implementation BLPlistModelManager

+ (NSArray *)getAllInstanceFromPlistWithClassName:(NSString *)className{
    NSMutableArray *array_m = [NSMutableArray new];
    //
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSArray *fileNameArray = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:documentsDirectory error:nil];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"self ENDSWITH %@ && self BEGINSWITH %@",@".plist",className];
    NSArray *filterFileNameArray = [fileNameArray filteredArrayUsingPredicate:predicate];
    for (NSString *name in filterFileNameArray) {
        NSString *path = [documentsDirectory stringByAppendingPathComponent:name];
        NSDictionary *dic = [[NSDictionary alloc]initWithContentsOfFile:path];
//        NSLog(@"dic %@",dic);
        
        id instance = [[NSClassFromString(className) alloc] init];
        
        
        
        NSArray *properties = [[self allPropertysOfClass:NSClassFromString(className)] allObjects];// 字符串数组，属性名称
        /* 循环的作用：把每个属性名当作Key，属性值当作Value，保存到Plist中;如果Value为nil，则不保存 */
        for (NSString *propertyName in properties) {
            
            // 从属性名称获得Setter方法
            NSString *capitalizedPropertyName = [propertyName stringByReplacingCharactersInRange:NSMakeRange(0,1) withString:[[propertyName substringToIndex:1] capitalizedString]];
            
            // The name of our auto synthesized setter | Custom setters will cause issues
            NSString * methodString = [NSString stringWithFormat:@"set%@:", capitalizedPropertyName];
            
            // Set our Selector
            SEL propertySetterSelector = NSSelectorFromString(methodString);
            if ([instance respondsToSelector:propertySetterSelector]) {
                // Index 0 is object, Index 1 is the selector: arguments start at Index 2
                const char * typeOfProperty = [self typeOfArgumentForSelector:propertySetterSelector instance:instance atIndex:2];
                // Set our implementation
                IMP imp = [instance methodForSelector:propertySetterSelector];
                
                if (dic[propertyName]) {
                    
                    // Get object from our dictionary
                    id objectFromDictionaryForProperty = dic[propertyName];
                    
                    // strcmp(str1, str2)
                    // 0 if same
                    // A value greater than zero indicates that the first character that does not match has a greater value in str1 than in str2;
                    // And a value less than zero indicates the opposite.
                    
                    // Set PlistValue to property
                    if (strcmp(typeOfProperty, @encode(id)) == 0) {
                        // NSLog(@"Is Object");
                        void (*func)(id, SEL, id) = (void *)imp;
                        func(instance, propertySetterSelector, objectFromDictionaryForProperty);
                    }
                    else if (strcmp(typeOfProperty, @encode(BOOL)) == 0) {
                        // NSLog(@"Is Bool");
                        void (*func)(id, SEL, BOOL) = (void *)imp;
                        func(instance, propertySetterSelector, [objectFromDictionaryForProperty boolValue]);
                    }
                    else if (strcmp(typeOfProperty, @encode(int)) == 0) {
                        // NSLog(@"Is Int");
                        void (*func)(id, SEL, int) = (void *)imp;
                        func(instance, propertySetterSelector, [objectFromDictionaryForProperty intValue]);
                    }
                    else if (strcmp(typeOfProperty, @encode(float)) == 0) {
                        // NSLog(@"Is Float");
                        void (*func)(id, SEL, float) = (void *)imp;
                        func(instance, propertySetterSelector, [objectFromDictionaryForProperty floatValue]);
                    }
                    else if (strcmp(typeOfProperty, @encode(double)) == 0) {
                        // NSLog(@"Is Double");
                        void (*func)(id, SEL, double) = (void *)imp;
                        func(instance, propertySetterSelector, [objectFromDictionaryForProperty doubleValue]);
                    }
                    
                }
                else {
                    
                    // Set PlistValue to property
                    if (strcmp(typeOfProperty, @encode(id)) == 0) {
                        //NSLog(@"Is Object");
                        void (*func)(id, SEL, id) = (void *)imp;
                        func(instance, propertySetterSelector, [NSNull new]);
                    }
                    else if (strcmp(typeOfProperty, @encode(BOOL)) == 0) {
                        //NSLog(@"Is Bool");
                        void (*func)(id, SEL, BOOL) = (void *)imp;
                        func(instance, propertySetterSelector, NO);
                    }
                    else if (strcmp(typeOfProperty, @encode(int)) == 0) {
                        //NSLog(@"Is Int");
                        void (*func)(id, SEL, int) = (void *)imp;
                        func(instance, propertySetterSelector, 0);
                    }
                    else if (strcmp(typeOfProperty, @encode(float)) == 0) {
                        //NSLog(@"Is Float");
                        void (*func)(id, SEL, float) = (void *)imp;
                        func(instance, propertySetterSelector, 0);
                    }
                    else if (strcmp(typeOfProperty, @encode(double)) == 0) {
                        //NSLog(@"Is Double");
                        void (*func)(id, SEL, double) = (void *)imp;
                        func(instance, propertySetterSelector, 0);
                    }
                }
            }
        }
        [array_m addObject:instance];
    }
    return [array_m copy];
}
+ (const char *)typeOfArgumentForSelector:(SEL)selector instance:(id)instance atIndex:(int)index {
    NSMethodSignature * sig = [instance methodSignatureForSelector:selector];
    
    if (index < sig.numberOfArguments) {
        // Index 0 is object, Index 1 is the selector itself, arguments start at Index 2
        const char * argType = [sig getArgumentTypeAtIndex:index];
        return argType;
    }
    else {
        NSLog(@"Index out of range of arguments");
        return nil;
    }
}
#pragma mark - 获得所有属性，包括子类和父类
+ (NSSet *)allPropertysOfClass:(Class)classInstance{
    NSMutableSet* result = [NSMutableSet new];
    Class observed = classInstance;
    while ([observed isSubclassOfClass:[BLPlistModel class]]) {
        [self propertyForClass: observed withSet: &result];
        observed = [observed superclass];// 每次循环，都获得父类
    }
    return result;
}

+ (void)propertyForClass: (Class)class withSet: (NSMutableSet **)result {
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

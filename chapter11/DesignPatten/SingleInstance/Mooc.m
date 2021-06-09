//
//  Mooc.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//


#import "Mooc.h"


@implementation Mooc



+ (id)sharedInstance
{
    // 静态局部变量
    static Mooc *instance = nil;
    
    // 通过dispatch_once方式 确保instance在多线程环境下只被创建一次
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        // 创建实例，这里用super未用self，是避免产生循环调用，又再次调用allocWithZone
        instance = [[super allocWithZone:NULL] init];
    });
    return instance;
}

// 重写方法【必不可少】如果直接allocwithzone也是可以创建对象的
+ (id)allocWithZone:(struct _NSZone *)zone{
    return [self sharedInstance];
}

// 重写方法【必不可少】外界可能会copy一个对象，为保证永远只创建一次，则这样写
- (id)copyWithZone:(nullable NSZone *)zone{
    return self;
}

@end

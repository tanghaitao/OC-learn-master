//
//  BridgeDemo.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "BridgeDemo.h"

#import "BaseObjectA.h"
#import "BaseObjectB.h"

#import "ObjectA1.h"
#import "ObjectA2.h"

#import "ObjectB1.h"
#import "ObjectB2.h"

@interface BridgeDemo()
@property (nonatomic, strong) BaseObjectA *objA;
@end

@implementation BridgeDemo

/*
 根据实际业务判断使用那套具体数据 a1的业务逻辑使用三套数据  a2的业务逻辑又可以使用不同的三套数据
 A1 --> B1、B2、B3         3种
 A2 --> B1、B2、B3         3种
 A3 --> B1、B2、B3         3种
 */
- (void)fetch
{
    // 创建一个具体的ClassA 创建的是业务a1 或 a2 或 a3
    _objA = [[ObjectA1 alloc] init];
    
    // 创建一个具体的ClassB， 针对业务创建实现获取不同数据 ObjectB1获取第一套数据 ObjectB2获取第三套数据
    BaseObjectB *b1 = [[ObjectB1 alloc] init];
    // 将一个具体的ClassB1 指定给抽象的ClassB
    _objA.objB = b1;
    
    // 获取数据
    [_objA handle];
}

@end

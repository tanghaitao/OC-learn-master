//
//  BaseObjectA.h
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/18.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseObjectB.h"
@interface BaseObjectA : NSObject

// 桥接模式的核心实现，它的成员是BaseObjectB 一个抽象类，不是具体的类，它是感知不到BaseObjectB的子类作了哪些事情的
@property (nonatomic, strong) BaseObjectB *objB;

// 获取数据
- (void)handle;

@end

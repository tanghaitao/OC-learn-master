//
//  BaseObjectB.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/18.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "BaseObjectB.h"

@implementation BaseObjectB
//获取数据的方法，什么都没有作，作为一个抽象类让子类去实现
- (void)fetchData
{
    // override to subclass
    NSLog(@"%@ == %@\n",NSStringFromClass([self class]),NSStringFromSelector(_cmd));
}

@end

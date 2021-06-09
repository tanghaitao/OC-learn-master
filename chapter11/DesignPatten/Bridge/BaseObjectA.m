//
//  BaseObjectA.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/18.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "BaseObjectA.h"
#import <objc/runtime.h>

@implementation BaseObjectA

 /*
    A1 --> B1、B2、B3         3种  control1调用了
    A2 --> B1、B2、B3         3种
    A3 --> B1、B2、B3         3种
  */
 //调用的是它成员的fetchData
- (void)handle
{
    // override to subclass
    NSLog(@"%@ == %@\n",NSStringFromClass([self class]),NSStringFromSelector(_cmd));
    [self.objB fetchData];
}

@end

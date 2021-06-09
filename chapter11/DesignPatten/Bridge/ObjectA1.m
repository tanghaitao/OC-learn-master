//
//  ObjectA1.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/18.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "ObjectA1.h"

@implementation ObjectA1
//覆写这个方法，写a1相关的业务逻辑
- (void)handle
{
    // before 业务逻辑操作
    NSLog(@"%@ == %@\n",NSStringFromClass([self class]),NSStringFromSelector(_cmd));
    [super handle];
    
    // after 业务逻辑操作
}


@end

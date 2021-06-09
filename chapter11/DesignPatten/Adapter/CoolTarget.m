//
//  CoolTarget.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "CoolTarget.h"

@implementation CoolTarget

- (void)request
{
    // 额外处理 适配逻辑 新增的业务功能
    
    [self.target operation];//[被适配对象 某方法] 比较老的功能需要保留的功能
    
    // 额外处理 适配逻辑 新增的业务功能
}

@end

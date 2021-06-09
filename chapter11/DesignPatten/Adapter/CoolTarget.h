//
//  CoolTarget.h
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "Target.h"

// 适配对象 是创建的适配器类新增的业务都写到这里
@interface CoolTarget : NSObject

// 被适配对象 需要被适配的类
@property (nonatomic, strong) Target *target;

// 对原有方法包装
- (void)request;

@end

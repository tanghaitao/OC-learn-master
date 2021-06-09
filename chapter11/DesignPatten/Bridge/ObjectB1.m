//
//  ObjectB1.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/18.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "ObjectB1.h"

@implementation ObjectB1
//这里覆写父类，写自己具体的逻辑，如下载对应的网络数据
- (void)fetchData{
    // 具体的逻辑处理
   NSLog(@"%@ == %@\n",NSStringFromClass([self class]),NSStringFromSelector(_cmd));
}

@end

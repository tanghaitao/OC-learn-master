//
//  UserCenter.m
//  GCD
//
//  Created by yangyang38 on 2018/3/16.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "UserCenter.h"

@interface UserCenter()
{
    // 定义一个并发队列
    dispatch_queue_t concurrent_queue;
    
    // 用户数据中心, 可能多个线程需要数据访问，这个存的是数据，可充许多个线程同时访问这个字典
    NSMutableDictionary *userCenterDic;
}

@end

// 多读单写模型
@implementation UserCenter

- (id)init
{
    self = [super init];
    if (self) {
        // 通过宏定义 DISPATCH_QUEUE_CONCURRENT 创建一个并发队列
        concurrent_queue = dispatch_queue_create("read_write_queue", DISPATCH_QUEUE_CONCURRENT);
        // 创建数据容器
        userCenterDic = [NSMutableDictionary dictionary];
    }
    
    return self;
}

- (id)objectForKey:(NSString *)key
{
    __block id obj;
    // 同步读取指定数据,多个读可并发执行，并同步立刻返回结果。满足同时并发返回调用结果
    dispatch_sync(concurrent_queue, ^{
        obj = [userCenterDic objectForKey:key];
    });
    
    return obj;
}
//当队列中的读操作完成，这会队列中任务为0时，才会执行dispatch_barrier_async中的代码，实现了多读单写的效果
- (void)setObject:(id)obj forKey:(NSString *)key
{
    //异步栅栏调用设置数据，在一个并发队列去写数据，
    dispatch_barrier_async(concurrent_queue, ^{
        [userCenterDic setObject:obj forKey:key];
    });
}

@end

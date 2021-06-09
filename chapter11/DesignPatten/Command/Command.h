//
//  Command.h
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//
//命令的抽象类，多个功能模块的命令可以创建多个此类的对象
#import <Foundation/Foundation.h>

@class Command;
typedef void(^CommandCompletionCallBack)(Command* cmd);//命令完成的回调，返回值是一个命令类型的对象

@interface Command : NSObject
@property (nonatomic, copy) CommandCompletionCallBack completion;

- (void)execute;//执行
- (void)cancel;//取消

- (void)done;//完成 如执行完成会block回调，告诉用户完成

@end

//
//  Command.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "Command.h"
#import "CommandManager.h"
@implementation Command

- (void)execute{
    
    //override to subclass; 定义很多抽象父类的命令子类去作自己想执行的逻辑
    
    [self done];//上面的逻辑完成之后调这个方法通知完成
}

- (void)cancel{
    
    self.completion = nil;//把回调为nil，获取不到回调则相当于未给上层通知
}

- (void)done
{
    //异步加到主队列，因为命令可能在子线程或不在子线程，需要这种方式回到调用方
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if (_completion) {
            _completion(self);
        }
        
        //释放block nil防止循环引用
        self.completion = nil;
        //调用命令管理者的移除操作把当前命令移除掉
        [[CommandManager sharedInstance].arrayCommands removeObject:self];
    });
}

@end

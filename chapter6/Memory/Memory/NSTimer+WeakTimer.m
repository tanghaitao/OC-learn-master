//
//  NSTimer+WeakTimer.m
//  Memory
//
//  Created by yangyang38 on 2018/3/4.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "NSTimer+WeakTimer.h"

@interface TimerWeakObject : NSObject
@property (nonatomic, weak) id target;
@property (nonatomic, assign) SEL selector;
@property (nonatomic, weak) NSTimer *timer;

- (void)fire:(NSTimer *)timer;
@end

@implementation TimerWeakObject

- (void)fire:(NSTimer *)timer
{
    if (self.target) {//判断如果当前持有的target存在，
        if ([self.target respondsToSelector:self.selector]) {//是否响应这个选择器，如果响应就回调下面这个方法
            [self.target performSelector:self.selector withObject:timer.userInfo];
        }
    }
    else{
        [self.timer invalidate];//不响应,已经释放了，就把timer置为无效，就达到timer强引用及弱引用的释放
    }
}

@end

@implementation NSTimer (WeakTimer)

+ (NSTimer *)scheduledWeakTimerWithTimeInterval:(NSTimeInterval)interval
                                         target:(id)aTarget
                                       selector:(SEL)aSelector
                                       userInfo:(id)userInfo
                                        repeats:(BOOL)repeats
{
    TimerWeakObject *object = [[TimerWeakObject alloc] init];//创建一个中间对象
    object.target = aTarget;//把这个target指给中间对象
    object.selector = aSelector;//把这个回调指给中间对象
    //调用系统的nstimer方法去创建nstimer，同时把它的回调方法指向中间对象的fire方法，
    //在fire方法当中再对实际对象的fire方法进行回调调用
    object.timer = [NSTimer scheduledTimerWithTimeInterval:interval target:object selector:@selector(fire:) userInfo:userInfo repeats:repeats];
    
    return object.timer;
}

@end

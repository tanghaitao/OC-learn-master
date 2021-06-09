//
//  RuntimeObject.m
//  RuntimeTest
//
//  Created by yangyang38 on 2018/2/25.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "RuntimeObject.h"
#import <objc/runtime.h>
@implementation RuntimeObject
+(void)load{
    //获取test方法的结构体
    Method test = class_getInstanceMethod(self,@selector(test));
    //获取otherTest方法的结构体
    Method otherTest = class_getInstanceMethod(self,@selector(otherTest));
    //交换两个方法的实现
    method_exchangeImplementations(test,otherTest);
    
    Class class = [self class];
    
//    SEL originalSelector = @selector(test);
//    SEL swizzledSelector = @selector(otherTest);
//    
//    Method originalMethod = class_getInstanceMethod(class, originalSelector);
//    Method swizzledMethod = class_getInstanceMethod(class, swizzledSelector);
//    
//    BOOL success = class_addMethod(class, originalSelector, method_getImplementation(swizzledMethod), method_getTypeEncoding(swizzledMethod));
//    if (success) {
//        
//        class_replaceMethod(class, swizzledSelector, method_getImplementation(originalMethod), method_getTypeEncoding(originalMethod));
//    } else {
//        method_exchangeImplementations(originalMethod, swizzledMethod);
//    }
}

-(void)test{
    NSLog(@"test");
}
//打印结果，选打印test,再打印了otherTest，当执行test方法时，执行的是[self otherTest],这个又相当于执行了test的实现打印了test,然后再打印NSLog(@"otherTest");
-(void)otherTest{
    //这里会产生死循环吗？不会，因为作了方法替换，在向该对向发送otherTest消息的时候，实际上是向test的实现发送了消息
    [self otherTest];
    NSLog(@"otherTest");
}


void testImp (void)
{
    NSLog(@"test invoke");
}

+ (BOOL)resolveInstanceMethod:(SEL)sel
{
    // 如果是test方法 打印日志
    
    if (sel == @selector(test)) {
        NSLog(@"resolveInstanceMethod:");
        
        // 动态添加test方法的实现  参数1：为该类对象添加方法 参数2：方法名称 参数3：方法实现 参数4:v，返回类型，@当前对象self，：方法的返回值类型 @selector(test)，对应的参数个数，参数类型，后面三个参数其实是method_t的成员变量
        
        // class_addMethod(self, @selector(test), testImp, "v@:");//会打印resolveInstanceMethod  test invoke
        
        return NO;
    }
    else{
        // 返回父类的默认调用
        return [super resolveInstanceMethod:sel];
    }
}

- (id)forwardingTargetForSelector:(SEL)aSelector
{
    NSLog(@"forwardingTargetForSelector:");
    return nil;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
    if (aSelector == @selector(test)) {
        NSLog(@"methodSignatureForSelector:");
        // v 代表返回值是void类型的  @代表第一个参数类型是id，即self
        // : 代表第二个参数是SEL类型的  即@selector(test)
        return [NSMethodSignature signatureWithObjCTypes:"v@:"];
    }
    else{
        return [super methodSignatureForSelector:aSelector];
    }
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    NSLog(@"forwardInvocation:");
}

@end

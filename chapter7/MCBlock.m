//
//  MCBlock.m
//  Block
//
//  Created by yangyang38 on 2018/3/5.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "MCBlock.h"

@implementation MCBlock

// 全局变量
int global_var = 4;
// 静态全局变量
static int static_global_var = 5;

- (void)method
{
    
//    //基本数据类型的局部变量
//    int var = 1;
//    //对象类型的局部变量
//    __unsafe_unretained id unsafe_obj = nil;
//    __strong id strong_obj = nil;
//    //局部静态变量
//    static int static_var = 3;
//    void(^Block)(void) = ^
//    {
//       //在block中使用到的变量，block会对变量进行截获
//       NSLog(@"局部变量<基本数据类型> var %d",var);//block中就是对值截获，作了赋值操作
//       //对象类型局部变量是把修饰符都一并传入到编译后的block代码，所以对象类型的所有权修饰符都是一并截获的
//       NSLog(@"局部变量<__unsafe_unretained 对象类型> var %@",unsafe_obj);
//       NSLog(@"局部变量<__strong 对象类型> var %@",strong_obj);
//       //int *static_var ，是截获了这个局部变量的指针，如果这个block方法体中是静态局部变量，因为它是指针截获，所以当静态局部变量值在block方法执行修改后，block方法体类的静态的值是会有所改变的
//       NSLog(@"局部静态变量 %d",static_var);
//       //block中未定义如下两个变量，所以不对全局变量截获
//       NSLog(@"全局变量 %d",global_var);
//       NSLog(@"静态全局变量 %d",static_global_var);
//    };
//    Block();
    
    __block int multiplier = 6;//12
//    static int multiplier = 6; //传入的是&multiplier,值会跟着变化。
//    int multiplier = 6;
//    int(^Block)(int) = ^int(int num)
//    {
//        return num * multiplier;
//    };
    
    //_blk是一个对象的block类型的成员变量，这里赋值实际上是一个copy，block会在堆上有另一拷贝
    _blk  = ^int(int num){
        return num * multiplier;
    };
    multiplier = 4;
//    Block(2);
//    NSLog(@"result is %d", Block(2));
    [self executeBlock];
    
//    NSMutableArray *array = [[NSMutableArray alloc] init];
//    void (^BLock)(void) = ^{
//        [array addObject:@123];//使用，并不是赋值操作，无需要添加block输出123
//    };
//    BLock();
//
//    __block NSMutableArray *array2= nil;//Variable is not assignable (missing __block type specifier)
//    void (^BLock2)(void) = ^{
//        array2 = [NSMutableArray array];
//        [array2 addObject:@123];//是赋值操作，需要添加block，输出123
//    };
//    BLock();
//    BLock2();
//
//    NSLog(@"arrary = %@",array2);
}

-(void)executeBlock{
    int result = _blk(4);
    NSLog(@"%d",result);
}

@end

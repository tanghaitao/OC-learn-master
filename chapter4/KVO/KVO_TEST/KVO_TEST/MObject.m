//
//  MObject.m
//  KVO_TEST
//
//  Created by yangyang38 on 2018/3/3.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "MObject.h"

@implementation MObject

- (id)init
{
    self = [super init];
    if (self) {
        _value = 0;
    }
    return self;
}
//-(void)setValue:(int)value{ //通过kvc设置value能否生效,会调用到这里
//    NSLog(@"%d",value);
//    _value = value;
//}

- (void)increase
{
    //直接为成员变量赋值，手动kvo
    [self willChangeValueForKey:@"value"];
    _value += 1;//_value += 1不会调用set方法，self.value +=1 会调用set方法
    [self didChangeValueForKey:@"value"];
}

@end

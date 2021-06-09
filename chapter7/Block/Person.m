//
//  Person.m
//  Block
//
//  Created by hai on 2020/12/16.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import "Person.h"
@interface Person()
//不作为公有属性，而是在对外方法接口中把Block传进来
@property (nonatomic ,copy) PersonBlock blk;
@end

@implementation Person
- (void)configurePersonBlock:(PersonBlock)blk_t{
    self.blk = blk_t;
}

- (void)actionComplete{
//    NSLog(@"%@",_cmd);
    self.blk();
}
@end

//
//  BlockRecycle.m
//  Block
//
//  Created by hai on 2020/12/8.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import "BlockRecycle.h"

@implementation BlockRecycle
- (void)method
{
    _array = [NSMutableArray arrayWithObject:@"block"];
    __weak NSArray *weakArray = _array;
    _strBlk = ^NSString *(NSString *num){
        return [NSString stringWithFormat:@"helloc_%@",weakArray.firstObject];
    };
    
    _strBlk(@"hello");
}
@end

//
//  BlockRecycle.h
//  Block
//
//  Created by hai on 2020/12/8.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BlockRecycle : NSObject
@property (nonatomic, strong)NSMutableArray *array;
@property (nonatomic, copy) NSString *(^strBlk)(NSString *);

- (void)method;
@end

NS_ASSUME_NONNULL_END

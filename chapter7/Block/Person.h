//
//  Person.h
//  Block
//
//  Created by hai on 2020/12/16.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef void (^PersonBlock)(void);

@interface Person : NSObject
@property (nonatomic ,assign) NSInteger age;
@property (nonatomic ,strong) NSString *name;
- (void)configurePersonBlock:(PersonBlock)blk_t;
- (void)actionComplete;
@end




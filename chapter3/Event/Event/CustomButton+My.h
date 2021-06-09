//
//  CustomButton+My.h
//  Event
//
//  Created by hai on 2020/12/2.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import <UIKit/UIKit.h>


#import "CustomButton.h"

NS_ASSUME_NONNULL_BEGIN

@interface CustomButton (My)
@property(nonatomic,copy)NSString *proName;//self.proName = @"333" 或者 self.proName; 都会奔溃
@end

NS_ASSUME_NONNULL_END

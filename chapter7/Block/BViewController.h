//
//  BViewController.h
//  Block
//
//  Created by hai on 2020/12/16.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Person.h"
NS_ASSUME_NONNULL_BEGIN

@interface BViewController : UIViewController
@property (nonatomic ,strong) Person *person;
@property (nonatomic ,copy) NSString *str;
@end

NS_ASSUME_NONNULL_END

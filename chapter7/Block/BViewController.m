//
//  BViewController.m
//  Block
//
//  Created by hai on 2020/12/16.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import "BViewController.h"


@implementation BViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.str = @"haha";
    
    self.person = [[Person alloc] init];
    self.person.name = @"commet";
    self.person.age = 18;
    
    __block Person *blkPerson = self.person;
    [self.person configurePersonBlock:^{
        NSLog(@"printf str:%@",self.str);
        self.person = nil;
        blkPerson = nil;
    }];
    [self.person actionComplete];
}
@end

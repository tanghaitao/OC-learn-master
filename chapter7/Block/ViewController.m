//
//  ViewController.m
//  Block
//
//  Created by yangyang38 on 2018/3/5.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "ViewController.h"
#import "BViewController.h"

@interface ViewController ()
@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    UIButton *btn = [[UIButton alloc]initWithFrame:CGRectMake(50, 150, 50, 50)];
    btn.backgroundColor = [UIColor redColor];
    [self.view addSubview:btn];
    [btn addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)click:(id)sender {
    BViewController *bVC = [[BViewController alloc]init];
    [self.navigationController pushViewController:bVC animated:YES];
}
@end

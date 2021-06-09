//
//  ViewController.m
//  GCD
//
//  Created by yangyang38 on 2018/3/15.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "ViewController.h"
#import "GroupObject.h"
#import "UserCenter.h"

@interface ViewController ()
{
    
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    UserCenter *user =  [[UserCenter alloc] init];
    
        dispatch_queue_t global_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_queue_t main_queue = dispatch_get_main_queue();
//    dispatch_queue_t serial_queue = dispatch_queue_create("otherQueue",DISPATCH_QUEUE_SERIAL);
//        //async底层没有分配runloop主线程
//        dispatch_async(global_queue,^{
//            NSLog(@"1== %@",[NSRunLoop currentRunLoop]);
////            [self performSelector:@selector(print) withObject:nil afterDelay:0];// 1 3
//            [self print];// 1 2 3
//    //        [self performSelectorOnMainThread:@selector(print) withObject:nil waitUntilDone:YES];// 1 2 3
//            NSLog(@"3");
//        });
    
    
    // Do any additional setup after loading the view, typically from a nib.
    /*
     同步串行
     NSLog(@"1");
     
     dispatch_sync(serial_queue,^{
     //       for (int i =0; i<1000; i++) {
     //           NSLog(@"2");
     //       }
     //       sleep(2);
     NSLog(@"2");
     
     
     
     });
     NSLog(@"3");
     */
    
    
    
//    NSLog(@"1");
//
//    //并发队列，并发执行，不是先进先出。串行队列，先进先出,2执行再执行3，3的执行不需要等待2执行完输出4再执行3
//    dispatch_sync(global_queue,^{
//        NSLog(@"2");
//        dispatch_sync(global_queue,^{
//            NSLog(@"3");
//        });
//        NSLog(@"4");
//    });
//    NSLog(@"5");
//    dispatch_async( main_queue, ^{
////        sleep(3);
//        [self print];
//    });
////    sleep(3);
//    NSLog(@"3");
    
}

-(void)print{
    NSLog(@"2");
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end

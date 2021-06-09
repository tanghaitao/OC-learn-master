//
//  AppDelegate.m
//  KVO_TEST
//
//  Created by yangyang38 on 2018/3/3.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "AppDelegate.h"
#import "MObject.h"
#import "MObserver.h"
#import <objc/runtime.h>
@interface AppDelegate ()
@property (nonatomic,copy)NSMutableArray *arraylist;
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
//    _arraylist = [[NSMutableArray alloc] init];
//    [self.arraylist addObject:@"23"];//奔溃 copy
    NSLog(@"=== %@",self.arraylist);
    MObject *obj = [[MObject alloc] init];
    MObserver *observer = [[MObserver alloc] init];
    
    //调用kvo方法监听obj的value属性的变化
    //调用kvo方法监听obj的value属性的变化，完成observer对obj对象value成员值临听
    //断点在这里的时候打印obj是mobserver
    [obj addObserver:observer forKeyPath:@"value" options:NSKeyValueObservingOptionNew context:NULL];
    Class class = object_getClass([MObject class]);
    NSLog(@"obj.name : %@\n, obj.class.name: %@",object_getClass(obj),class);
    //通过setter方法修改value
    //通过setter方法修改value，这时候value值变了，所以MObserver中的方法会临听到
    //断点在这里的时候打印obj是nskvonotifying_MObserver,isa指针已经重新指向了
    obj.value = 1;
    obj.value = 2;
    
    // 1 通过kvc设置value能否生效？
    [obj setValue:@3 forKey:@"value"];
    /*
     问题一是在描述kvo与kvc之间的关系，这个是能生效的。为什么kvc设置value会使kvo生效呢？因为这个方法最
     终会调用obj中的setter方法，所以setter又是重写的，就能生效。
     */
    
    // 2. 通过成员变量直接赋值value能否生效?
    //为使生效，在increase方法手动让kvo生效，加入 willChangeValueForKey，
    //didChangeValueForKey就可监听到kvo的
    [obj increase];
    
    return YES;
}
-(NSMutableArray *)arraylist{
    if (!_arraylist) {
        _arraylist = [NSMutableArray array];
    }
    return _arraylist;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end

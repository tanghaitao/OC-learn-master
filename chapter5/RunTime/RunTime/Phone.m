//
//  Phone.m
//  RunTime
//
//  Created by hai on 2020/12/3.
//  Copyright © 2020 yangyang. All rights reserved.
//

#import "Phone.h"

@implementation Phone
-(id)init
{
  self = [super init];
  if(self){
      // 输出的都是[self class] === Phone
      NSLog(@"[self class] === %@\n",NSStringFromClass([self class]));//消息的接收者是当前对象，class这个方法是在nsobject当中才有实现的
      NSLog(@"[super class] === %@",NSStringFromClass([super class]));
      /*
       super调用它的class实际接收者任然是当前对象，也就是phone，
      调super class是从当前对象的父类对象中开始查找方法实现，无论从哪查找都是找到nsobject当中，因为这里面有class方法
       */
  }
    return  self;
}
@end

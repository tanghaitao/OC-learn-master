//
//  BusinessObject.h
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BusinessObject;//相当于业务 a b c
typedef void(^CompletionBlock)(BOOL handled);//表达某一业务处理完成之后，返回的结果代表它是否有处理对应的业务
typedef void(^ResultBlock)(BusinessObject *handler, BOOL handled);//业务最终处理者 参数2表达是否有处理这业务


@interface BusinessObject : NSObject

// 下一个响应者(响应链构成的关键) 定义和当前类类型相同的成员变量，就组成了基本的责任链结构
@property (nonatomic, strong) BusinessObject *nextBusiness;
// 响应者的处理方法，作为响应链的入口函数
- (void)handle:(ResultBlock)result;

// 各个业务在该方法当中做实际业务处理，完成后通过block作为业务结果返回，因为可能有异步网络请示，用block
- (void)handleBusiness:(CompletionBlock)completion;
@end

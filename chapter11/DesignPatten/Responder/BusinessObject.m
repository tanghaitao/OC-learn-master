//
//  BusinessObject.m
//  DesignPatten
//
//  Created by yangyang38 on 2018/3/17.
//  Copyright © 2018年 yangyang. All rights reserved.
//

#import "BusinessObject.h"

@implementation BusinessObject

// 责任链入口方法
- (void)handle:(ResultBlock)result
{
    CompletionBlock completion = ^(BOOL handled){
        
        if (handled) {// 当前业务处理掉了，上抛结果
            result(self, handled);//处理了返回当前处理的对象以及返回结果
        }
        else{//没处理掉
            // 沿着责任链，指派给下一个业务处理，a业务处理完如果再处理b业务会走这段代码
            if (self.nextBusiness) {
                [self.nextBusiness handle:result];//递归的去调用
            }
            else{// 没有业务处理, 上抛，a后面没有其它业务如b,c会返回这个处理结果
                result(nil, NO);
            }
        }
    };
    
    // 当前业务进行处理, 这里就是不同的业务a,b,c，相当于当前不同的类对象，作不同的业务处理，如a业务处理完成之后就会调用上面代码的block
    [self handleBusiness:completion];
}

- (void)handleBusiness:(CompletionBlock)completion
{
    /*
     业务逻辑处理
     如网络请求、本地照片查询等
     */
}

@end

//
//  MergeSortedList.m
//  Arithmetic
//
//  Created by kevin on 2018/3/26.
//  Copyright © 2018年 imooc. All rights reserved.
//

#import "MergeSortedList.h"

@implementation MergeSortedList

void mergeList(int a[], int aLen, int b[], int bLen, int result[])
{
    int p = 0; // 遍历数组a的指针
    int q = 0; // 遍历数组b的指针
    int i = 0; // 记录当前存储位置，当前比较最小的那个值应该存储到新数组的哪个位置
    
    // 任一数组没有到达边界则进行遍历，p,q都不能超过本身数组的长度
    while (p < aLen && q < bLen) {
        // 如果a数组对应位置的值小于b数组对应位置的值，就要把a数组的元素放入合并结果中，同时移动a数组
        if (a[p] <= b[q]) {
            // 存储a数组的值
            result[i] = a[p];
            // 移动a数组的遍历指针
            p++;
        }
        else{
            // 存储b数组的值
            result[i] = b[q];
            // 移动b数组的遍历指针
            q++;
        }
        // 指向合并结果的下一个存储位置
        i++;
    }
    //如果要去重的话，if (= ){result[I] = ap[p];p++;q++; }即可
    // 如果a数组有剩余，因为上面 while (p < aLen && q < bLen) ，是与，所以这里肯定会有余下的情况
    while (p < aLen) {
        // 将a数组剩余部分拼接到合并结果的后面
        result[i] = a[p++];
        i++;
    }
    
    // 如果b数组有剩余
    while (q < bLen) {
        // 将b数组剩余部分拼接到合并结果的后面
        result[i] = b[q++];
        i++;
    }
}

-(void)math
{
    int a[5] = {1,4,6,7,9};
    int b[8] = {2,3,5,6,8,10,11,12};
    int result[13];
    mergeList(a,5,b,8,result);
    
}

@end

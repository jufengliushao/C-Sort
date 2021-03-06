//
//  SFMergeSort.h
//  CSortDemo
//
//  Created by shaofeng liu on 2018/10/2.
//  Copyright © 2018年 shaofeng liu. All rights reserved.
//

#ifndef SFMergeSort_h
#define SFMergeSort_h

#include <stdio.h>

//归并排序
void merge_sort(char **a, int start, int end);

// 第二阶段排序
int merge_secondSort(char **buffer1, char **buffer2, char **sort);

#endif /* SFMergeSort_h */

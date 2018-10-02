//
//  SFMergeSort.c
//  CSortDemo
//
//  Created by shaofeng liu on 2018/10/2.
//  Copyright © 2018年 shaofeng liu. All rights reserved.
//

#include "SFMergeSort.h"
#include <stdlib.h>
#include <string.h>
#include "PublicDefineHeader.h"

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
//合并数组的前半部分和后半部分， 前提就是前后两个子数组分别都已经排好序了
void mergeArray(char **a, int first, int mid, int last);
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

//归并排序
void merge_sort(char **a, int start, int end) {
    int mid = (start+end)/2;
    if(start<end) {
        merge_sort(a, start, mid);
        merge_sort(a, mid+1, end);
        mergeArray(a, start, mid, end);
    }
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

//合并数组的前半部分和后半部分， 前提就是前后两个子数组分别都已经排好序了
void mergeArray(char **a, int first, int mid, int last) {
    
    int i, j, m, n;
    i = first;
    m = mid;
    j = mid+1;
    n = last;
    int k = 0;
    long size = RAM_MEMORY * SIZE_GMKB / BLOCK_MEMORY * 40;
    char **temp = (char **)malloc(size * sizeof(long));
    
    while(i<=m && j<=n) {
        if(strcmp(a[i], a[j]) < 0) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    
    while(i<=m) temp[k++] = a[i++];
    while(j<=n) temp[k++] = a[j++];
    
    for(i=0; i<k; i++) {
        a[first+i] = temp[i];
    }
    free(temp);
}

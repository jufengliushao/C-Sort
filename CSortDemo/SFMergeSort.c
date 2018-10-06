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

/**
 * 第二阶段排序
 * 0 - 输出区满了
 * 1 - 第一个buffer空了
 * 2 - 第二个buffer空了
 * 3 - 全空了
 */
int merge_private_secondSort(char **buffer1, char **buffer2, char **sort, long *count1, long *count2, long *sortIndex, char *bigger);
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

// 第二阶段排序
int merge_secondSort(char **buffer1, char **buffer2, char **sort){
    long *count1 = (long *)malloc(sizeof(long));
    long *count2 = (long *)malloc(sizeof(long));
    long *sortIn = (long *)malloc(sizeof(long));
    *count1 = *count2 = *sortIn = 0;
    char bigger[LINE_LENGTH];
    return merge_private_secondSort(buffer1, buffer2, sort, count1, count2, sortIn, bigger);
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

/**
 * 第二阶段排序
 * 0 - 输出区满了
 * 1 - 第一个buffer空了
 * 2 - 第二个buffer空了
 * 3 - 全空了
 */
int merge_private_secondSort(char **buffer1, char **buffer2, char **sort, long *count1, long *count2, long *sortIndex, char *bigger) {
    if(*sortIndex >= CACHE_SECTION){
        return 0;
    }else if (strlen(buffer1[*count1]) < 10 && strlen(buffer2[*count2]) < 10) {
        return 3;
    }else if (strlen(buffer1[*count1]) < 10){
        return 1;
    }else if(strlen(buffer2[*count2]) < 10){
        return 2; // 第二个buffer空了
    }
    
    char **tmp;
    long *tmpIndex;
    if (strcmp(buffer1[*count1], buffer2[*count2]) < 0) {
        tmp = buffer1;
        bigger = buffer2[*count2];
        tmpIndex = count1;
    }else{
        tmp = buffer2;
        bigger = buffer1[*count1];
        tmpIndex = count2;
    }
    
    while ((*tmpIndex) < CACHE_SECTION && (*sortIndex) < CACHE_SECTION && strlen(tmp[*tmpIndex]) > 10 && strcmp(tmp[*tmpIndex], bigger) <= 0) {
        sort[(*sortIndex) ++] = tmp[(*tmpIndex) ++];
        if ((*sortIndex) == 149498) {
            printf("");
        }
    }
    return merge_private_secondSort(buffer1, buffer2, sort, count1, count2, sortIndex, bigger);
}

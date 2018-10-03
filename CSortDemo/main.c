//
//  main.c
//  CSortDemo
//
//  Created by shaofeng liu on 2018/10/2.
//  Copyright © 2018年 shaofeng liu. All rights reserved.
//

#include <stdio.h>
#include "SFFileManager.h" // 文件读写类
#include "SFMergeSort.h"

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
/**
 * 数据初始化
 */
void initingData(void);

/**
 * 第一阶段数据排序
 */
void firstSortData(int index);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------


int main(int argc, const char * argv[]) {
    initingData();
    int i = 0;
    int firstCount = (int)malloc(sizeof(int));
    firstCount = SOURCE_DATA_MEMORY * SIZE_GMKB / RAM_MEMORY;
    for (i = 0; i < firstCount; i ++) {
      firstSortData(i);
    }
    file_closeReadOnly();
    return 0;
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
/**
 * 数据初始化
 */
void initingData() {
    file_createFile(FILE_SOURCE_NAME); // 创建source文件
    file_createFile(FILE_SORT_ONE_NAME); // 创建sort1文件
    file_createFile(FILE_SORT_TWO_NAME); // 创建sort2文件
    file_writeSource();
}

/**
 * 第一阶段数据排序
 */
void firstSortData(int index) {
    char *path = (char *)malloc(200);
    strcpy(path, FILE_PRIFX);
    strcat(path, FILE_SORT_ONE_NAME);
    long sizes = RAM_MEMORY * SIZE_GMKB / BLOCK_MEMORY * 40;
    char **re = (char **)malloc(sizes * sizeof(long));
    for (long i = 0; i < sizes; i ++) {
        re[i] = (char *)malloc(sizeof(char) * LINE_LENGTH);
    }
    file_readData(re);
    merge_sort(re, 0, sizes - 1);
    struct FilePoint point;
    point.filePath = (char *)malloc(sizeof(char) * 200);
    strcpy(point.filePath, path);
    point.flag = 0;
    point.offset = sizes * index;
    point.maxRecords = sizes;
    file_writeSortedData(&point, re);
    free(re);
    free(path);
}

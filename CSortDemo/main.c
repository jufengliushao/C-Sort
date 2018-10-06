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
struct FilePoint points[20]; // 点
int pointsCount = 0; // 当前一个数据结构index
/**
 * 数据初始化
 */
void initingData(void);

/**
 * 第一阶段数据排序
 */
void firstSortData(int index);

/**
 * 第二阶段排序
 */
void secondSortData(void);
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------


int main(int argc, const char * argv[]) {
//    initingData();
    int i = 0;
    int firstCount = (int)malloc(sizeof(int));
    firstCount = SOURCE_DATA_MEMORY * SIZE_GMKB / RAM_MEMORY;
    for (i = 0; i < 1; i ++) {
      firstSortData(i);
    }
    file_closeReadOnly();
    secondSortData();
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
        re[i] = (char *)malloc(sizeof(char) * LINE_LENGTH + 1);
    }
    file_readData(re);
    merge_sort(re, 0, sizes - 1);
    struct FilePoint point;
    point.filePath = (char *)malloc(sizeof(char) * 200);
    strcpy(point.filePath, path);
    point.flag = 3;
    point.offset = sizes * index;
    point.maxRecords = sizes;
    int indexs = sizeof(points) / sizeof(struct FilePoint);
    points[pointsCount++] = point;
    file_writeSortedData(&point, re);
    free(re);
    free(path);
}

/**
 * 第二阶段排序
 */
void secondSortData() {
    // 获取两个points
    struct FilePoint tmpPoint[2];
    int count = sizeof(points) / sizeof(points[0]), j = 0;
    for (int i = 0; i < count; i ++) {
        if(points[i].flag == 3){
            tmpPoint[j++] = points[i];
        }
        if (j >= 2) {
            break;
        }
    }
    
    char **buffer1 = (char **)malloc(CACHE_SECTION * sizeof(long));
    char **buffer2 = (char **)malloc(CACHE_SECTION * sizeof(long));
    char **sort = (char **)malloc(CACHE_SECTION * sizeof(long));
    for (long i = 0; i < CACHE_SECTION; i ++) {
        buffer1[i] = (char *)malloc(sizeof(char) * LINE_LENGTH);
        buffer2[i] = (char *)malloc(sizeof(char) * LINE_LENGTH);
    }
    file_readSectionData(buffer1, &tmpPoint[0]);
    file_readSectionData(buffer2, &tmpPoint[1]);
    int flag = merge_secondSort(buffer1, buffer2, sort);
    free(buffer1);
    free(buffer2);
    free(sort);
}

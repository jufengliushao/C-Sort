//
//  SFFileManager.c
//  CSortDemo
//
//  Created by shaofeng liu on 2018/10/2.
//  Copyright © 2018年 shaofeng liu. All rights reserved.
//

#include "SFFileManager.h"

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
/**
 * 创建文件
 */
int file_private_createFile(char *path);

/**
 * 打开文件
 * path - 文件路径
 * fp - 打开文件指针
 * openStyle - 打开方式
 */
int file_private_openFile(char *path, FILE **fp, char *openStyle);

/**
 * 随机创建元数据文件
 * 0 - success 1 - fail
 */
int file_private_writeSourceData(void);

/**
 * 获取随机数
 */
long file_private_randNum(void);

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

/**
 * 创建文件
 * 0 - success 1 - fail 2 - file name empty
 */
int file_createFile(char *path) {
    if (sizeof(path) < 3) {
        return 2;
    }
    return file_private_createFile(path);
}

/**
 * 进行数据的读写
 */
void file_writeSource() {
    file_private_writeSourceData();
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
/**
 * 创建文件
 */
int file_private_createFile(char *path) {
    char *filePath = (char *)malloc(1000);
    strcpy(filePath, FILE_PRIFX);
    strcat(filePath, path);
    FILE *fp;
    if ((fp = fopen(filePath, "w+")) == NULL) {
        free(filePath);
        return 1;
    }
    fclose(fp);
    free(filePath);
    return 0;
}

/**
 * 打开文件
 * path - 文件路径
 * fp - 打开文件指针
 * openStyle - 打开方式
 * 0 - success 1 - fail
 */
int file_private_openFile(char *path, FILE **fp, char *openStyle){
    if ((*fp = fopen(path, openStyle)) == NULL) {
        return 1;
    }
    return 0;
}

/**
 * 随机创建元数据文件
 * 0 - success 1 - fail
 */
int file_private_writeSourceData() {
    char *path = (char *)malloc(2000);
    FILE *fp;
    strcpy(path, FILE_PRIFX);
    strcat(path, FILE_SOURCE_NAME);
    long i = 0;
    long records = SOURCE_DATA_MEMORY * SIZE_GMKB * SIZE_GMKB * SIZE_GMKB / 100;
    fp = fopen(path, "a+");
    while (i < records) {
        char *writeData = (char *)malloc(sizeof(char) * LINE_LENGTH);
        char *numStr = (char *)malloc(10);
        sprintf(numStr, "%ld", file_private_randNum());
        strcat(writeData, numStr);
        strcat(writeData, SUFFIX_DATA);
        fwrite(writeData, LINE_LENGTH, 1, fp);
        writeData = NULL;
        numStr = NULL;
        i ++;
    }
    free(path);
    fclose(fp);
    return 0;
}

/**
 * 获取随机数
 */
long file_private_randNum() {
    long rand = random();
    while (rand / 1000000000 == 0) {
        rand *= 10;
    }
    return rand;
}

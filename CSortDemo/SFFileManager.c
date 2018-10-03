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

FILE *fp_readConst;
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

/**
 * 对排序好的数据进行写入文件
 */
void file_private_writeData(struct FilePoint point, char **buffer);

/**
 * 读数据 - 按扇区
 */
void file_private_secondSectionReadData(char **buffer, struct FilePoint *point);

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

/**
 * 读取数据
 */
void file_readData(char **lineBlock){
    if (fp_readConst == NULL) {
        char *path = (char *)malloc(sizeof(200));
        strcpy(path, FILE_PRIFX);
        strcat(path, FILE_SOURCE_NAME);
       fp_readConst = fopen(path, "r");
    }
    // 打开文件成功
    long count = RAM_MEMORY * SIZE_GMKB / BLOCK_MEMORY * 40;
    long i = 0;
    while (i < count) {
        char *buffer = (char *)malloc(LINE_LENGTH);
        fgets(buffer, LINE_LENGTH, fp_readConst);
        if(strlen(buffer) < 10){
            free(buffer);
            continue;
        }
        strcpy(lineBlock[i], buffer);
        i ++;
        free(buffer);
    }
}

/**
 * 关闭只读指针
 */
void file_closeReadOnly() {
    fclose(fp_readConst);
}

/**
 * 排序好的数据进行r写入文件
 */
void file_writeSortedData(struct FilePoint *point, char **buffer) {
    file_private_writeData(*point, buffer);
}

/**
 * 按照数据结构，第二阶段读取数据
 */
void file_readSectionData(char **buffer, struct FilePoint *point) {
    (*point).flag = 1; // 标记为正在读取数据
    file_private_secondSectionReadData(buffer, point);
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

/**
 * 对排序好的数据进行写入文件
 */
void file_private_writeData(struct FilePoint point, char **buffer){
    FILE *fp;
    if ((fp = fopen(point.filePath, "a+")) == NULL) {
        // 打开文件失败
        return;
    }
    long count = point.maxRecords;
    long i = 0;
    while (i < count) {
        fwrite(strcat(buffer[i], "\n"), LINE_LENGTH, 1, fp);
        i ++;
    }
    fclose(fp);
}

/**
 * 读数据 - 按扇区
 */
void file_private_secondSectionReadData(char **buffer, struct FilePoint *point) {
    FILE *fp;
    if((fp = fopen((*point).filePath, "r")) == NULL){
        return; // 打开失败
    }
    fseek(fp, (*point).offset * LINE_LENGTH, SEEK_SET);
    long i = 0, count = CACHE_SECTION;
    while (i < count) {
        char *buffers = (char *)malloc(LINE_LENGTH);
        fgets(buffers, LINE_LENGTH, fp);
        if(strlen(buffers) < 10){
            free(buffers);
            continue;
        }
        strcpy(buffer[i], buffers);
        i ++;
        (*point).maxRecords --;
        if ((*point).maxRecords <= 0) {
            break;
        }
    }
    (*point).offset += --i;
    fclose(fp);
}

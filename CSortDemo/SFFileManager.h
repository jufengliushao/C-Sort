//
//  SFFileManager.h
//  CSortDemo
//
//  Created by shaofeng liu on 2018/10/2.
//  Copyright © 2018年 shaofeng liu. All rights reserved.
//

#ifndef SFFileManager_h
#define SFFileManager_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "PublicDefineHeader.h"

/**
 * 创建文件
 * 0 - success 1 - fail 2 - file name empty
 */
int file_createFile(char *path);

/**
 * 进行数据的读写
 */
void file_writeSource(void);

/**
 * 关闭只读指针
 */
void file_closeReadOnly(void);

/**
 * 读取数据
 */
void file_readData(char **lineBlock);

/**
 * 排序好的数据进行写入文件
 */
void file_writeSortedData(struct FilePoint *point, char **buffer);

/**
 * 按照数据结构，第二阶段读取数据
 */
void file_readSectionData(char **buffer, struct FilePoint *point);
#endif /* SFFileManager_h */

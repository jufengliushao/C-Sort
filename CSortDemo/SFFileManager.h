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

#endif /* SFFileManager_h */

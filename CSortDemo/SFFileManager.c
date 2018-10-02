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

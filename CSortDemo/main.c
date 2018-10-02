//
//  main.c
//  CSortDemo
//
//  Created by shaofeng liu on 2018/10/2.
//  Copyright © 2018年 shaofeng liu. All rights reserved.
//

#include <stdio.h>
#include "SFFileManager.h" // 文件读写类

int main(int argc, const char * argv[]) {
    file_createFile(FILE_SOURCE_NAME); // 创建source文件
    file_createFile(FILE_SORT_ONE_NAME); // 创建sort1文件
    file_createFile(FILE_SORT_TWO_NAME); // 创建sort2文件
    file_writeSource();
    return 0;
}

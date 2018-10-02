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
int main(int argc, const char * argv[]) {
    /*
    file_createFile(FILE_SOURCE_NAME); // 创建source文件
    file_createFile(FILE_SORT_ONE_NAME); // 创建sort1文件
    file_createFile(FILE_SORT_TWO_NAME); // 创建sort2文件
    file_writeSource();
     */
    
    char **re = (char **)malloc(8);
    char res[8][5] = {"a1", "a8", "a2", "a1", "a5", "a6", "a4", "a7"};
    for (int i = 0; i < 8; i ++) {
        re[i] = (char *)malloc(5);
        re[i] = res[i];
    }
    merge_sort(re, 0, 7);
    for (int i = 0; i < 8; i ++) {
        printf("%s ", re[i]);
    }
    return 0;
}

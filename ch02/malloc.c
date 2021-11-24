/**
 * @file malloc.c
 * 2.1.3
 * mallocの確認用コード
 */

#include <stdio.h>
#include <stdlib.h> // exit, free, malloc

int main(void)
{
    // int用のメモリ領域を確保
    int *p = malloc(sizeof(int));
    if (p == NULL) {
        // 確保失敗
        perror("malloc");
        exit(1);
    }

    // mallocが確保した領域に99を代入する
    *p = 99;
    printf("%d\n", *p);
    
    // メモリ領域解放
    free(p);
}
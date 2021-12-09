/**
 * @file trunc10.c
 * 
 * 3.15 truncate
 * ファイルサイズを切り詰める
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    // 指定したパスのファイルのサイズを10バイトにする
    if (truncate("ch03/hello.txt", 10) == -1) {
        perror("truncate");
        exit(1);
    }
    return 0;
}
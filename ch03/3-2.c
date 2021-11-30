/**
 * @file 3-2.c
 * 
 * ファイルを開いてすぐに閉じることでからのファイルを作る
 * 
 * 作成するファイル名はempty.fileとする
 * 既にファイルがあるなら、そのファイルの内容を空(0)にする
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    // 読み取り専用 ファイルがなければ作成 ファイルがあれば長さ0にtruncateする ファイル作成する場合は644の権限
    int fd = open("ch03/empty.file", O_RDONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
    }
    int result = close(fd);
    if (result == -1) {
        perror("close");
    }
    return 0;
}
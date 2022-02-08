/**
 * @file myls0.c
 * 
 * ディレクトリストリームを使った簡単なls
 */
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void)
{
    DIR *dirp; // ディレクトリストリーム
    struct dirent *p; // ディレクトリ項目用の構造体 readdirで取得する

    // カレントディレクトリのディレクトリストリームを取得
    if ((dirp = opendir(".")) == NULL) {
        perror("opendir");
        exit(1);
    }
    errno = 0;
    // ディレクトリ項目がなくなるまでreaddirする
    while((p = readdir(dirp)) != NULL) {
        // ファイル名とiノード番号を表示する。
        printf("filename: %s, inode: %llu\n", p->d_name, p->d_ino);
    }

    if (errno != 0) {
        perror("readdir");
        exit(1);
    }

    // ディレクトリストリームを閉じる
    if (closedir(dirp) != 0) {
        perror("closedir");
        exit(1);
    }
    return 0;
}
/**
 * @file lns.c
 * 
 * 演習問題6.6 ln -sを作る
 * シンボリックリンクを作成するプログラム
 * 
 * ./lns path1 path2実行し
 * path1を示すシンボリックリンクをpath2という名前で作る
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s <file> <symbolik link>", argv[0]);
        exit(1);
    }

    if (symlink(argv[1], argv[2]) != 0) {
        perror("symlink");
        exit(1);
    }

    printf("symlink success! file:%s, symbolik link:%s", argv[1], argv[2]);

    return 0;
}

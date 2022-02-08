/**
 * @file cdpwd.c
 * 
 * 演習問題6.5 chdirを使って親ディレクトリに移動し、そのディレクトリの絶対パス名を表示する
 * プログラム終了後、作業ディレクトリはどうなっているか?
 * -> プロセス自身の作業ディレクトリを変えるだけで、おやプロセスであるシェルの作業ディレクトリは変えない
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char buf[PATH_MAX + 1];

    // 現在のディレクトリを表示する
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd");
        exit(1);
    }
    printf("current directory path:%s\n", buf);

    // ..で親ディレクトリに変更する
    if (chdir("..") == -1) {
        perror("chdir");
        exit(1);
    }
    // 親ディレクトリを表示する
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd");
        exit(1);
    }
    printf("parent directory path:%s\n", buf);
    return 0;
}
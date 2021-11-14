#include <stdio.h>
#include <unistd.h> // rmdir
#include <stdlib.h>
#include <errno.h>

/**
 * 1-7.cの改良版
 * ディレクトリが削除できない場合に、fooの中のファイル一覧を表示するようにする
 */
int main(void) {
    int res = rmdir("foo");
    if (res == -1) {
        // perrorの実行でerrnoが変わりうるので、old_errnoに退避させる
        int old_errno = errno;
        perror("rmdir");
        // errrnoをチェック
        // ディレクトリが空でない場合 ディレクトリ配下のファイルを表示させる
        if (old_errno == ENOTEMPTY) {
            system("ls foo");
        }
        exit(1);
    }
    exit(0);
}

/**
 * 1-7.cの改良版回答
 * perrorを先にやるべき
 */
int main2(void) {
    int res = rmdir("foo");
    if (res == -1) {
        printf("%d", errno);
        // errrnoをチェック
        // ディレクトリが空でない場合 ディレクトリ配下のファイルを表示させる
        if (errno == ENOTEMPTY) {
            system("ls foo");
        }
        perror("rmdir");
        exit(1);
    }
    exit(0);
}
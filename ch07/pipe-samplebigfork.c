/**
 * @file pipe-samplebigfork.c
 * 
 * 演習問題7.4
 * 
 * 演習問題7.3を改良し、親プロセスが大きなデータ(例: 1MB)をパイプに書き込んでもパイプ詰まりが起こらず
 * 子プロセスが問題なくデータを読めることを確認する
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>

enum {
    SIZE = 1024 * 1024
};

int main(void)
{
    int fd, pipe_fd[2], nbytes;
    char buf [SIZE], buf2[SIZE];

    // パイプの作成
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // fork
    if ((fd = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (fd == 0) {
        // 子プロセス
        // 子プロセスの書き込み用fdを閉じる
        close(pipe_fd[1]);

        fprintf(stderr, "[child] child process start. reading from pipe.\n");

        nbytes = read(pipe_fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, nbytes);

        // パイプの後処理
        close(pipe_fd[0]);
    } else {
        // 親プロセス
        // 親プロセスの読み取り用fdを閉じる
        close(pipe_fd[0]);
        fprintf(stderr, "[parent] parent process start. writing to pipe.\n");
        
        // 1MBのデータをパイプへ書き込む
        // バッファの上限を超えているデータサイズ
        write(pipe_fd[1], buf2, sizeof(buf2));

        // パイプの後処理
        close(pipe_fd[1]);

        // 子プロセスの終了を待つ。
        wait(NULL);
    }
    return 0;

}
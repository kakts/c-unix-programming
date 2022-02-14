/**
 * @file pipe-samplefork.c
 * 
 * 演習問題7.3
 * 
 * パイプを使って親プロセスから子プロセスにメッセージ Hello\nを送るようにする
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>

int main(void)
{
    int fd, pipe_fd[2], nbytes;
    char buf [1024];

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
        
        // パイプへ書き込む
        write(pipe_fd[1], "Hello\n", 6);

        // パイプの後処理
        close(pipe_fd[1]);

        // 子プロセスの終了を待つ。
        wait(NULL);
    }
    return 0;

}
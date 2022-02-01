/**
 * @file mysh1.c
 * 
 * ch05 5.10 wait q5.9
 * シンプルなシェルプログラム
 * 
 * mysh0.cを改良し、子プロセスがexitで終了した場合にその終了コードを表示するシェルを作る
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../sub/mysub.h"

int main(void)
{
    char cmd[1024];
    int status;

    for (;;) {
        getstr("@ ", cmd, sizeof(cmd));
        if (fork() == 0) {
            // 子プロセス
            // 引数なし
            execlp(cmd, cmd, (char *)0);
            perror(cmd);
            exit(1);
        }

        // 親プロセス
        // 子プロセスの終了を待つ
        if (wait(&status) == (pid_t) -1) {
            perror("wait");
            exit(1);
        }

        // 子プロセスがexitで終了した場合
        if (WIFEXITED(status)) {
            printf("child process exited. signal %d", WEXITSTATUS(status));
        }
    }
    exit(0);
}
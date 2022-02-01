/**
 * @file mysh0.c
 * 
 * ch05 5.10 wait
 * シンプルなシェルプログラム
 * 
 * 繰り返しの先頭でプロンプトを表示し、ユーザからコマンドを受け取る。
 * 
 * おやプロセスはforkで子プロセスを作った後すぐにwaitを呼び出して子プロセスの終了を待つ。
 * 子プロセスは入力されたコマンドをexeclpで実行する
 * 引数の処理をしていないので、コマンドには引数を与えられない。
 * 子プロセスが終了するとおやプロセスはwaitから戻り、繰り返しの先頭に戻って再びプロンプトを表示する。
 * statusには子プロセスの状態を示す値が入る。この値に対して関数マクロを適用することで子プロセスの状態がわかる。
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
    }
    exit(0);
}
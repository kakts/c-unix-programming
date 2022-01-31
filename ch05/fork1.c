/**
 * @file fork1.c
 * 
 * 5.5 fork1.c
 * 親プロセスと子プロセスで別の動作をさせる。
 * 
 * forkの戻り値で判定する。
 * 子プロセスの場合、forkの戻り値は0となる
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int i;
    pid_t cpid;

    if ((cpid = fork()) == -1) {
        // error
        perror("fork");
        exit(1);
    } else if (cpid == 0) {
        // 子プロセス
        for (i = 0; i < 10; i++) {
            printf("<%d>", i);
            fflush(stdout);
            sleep(1);
        }
        // 子プロセスのexit
        exit(0);
    }

    // 親プロセス
    for (i = 9; i >= 0; i--) {
        printf("[%d]", i);
        fflush(stdout);
        sleep(2);
    }
    putchar('\n');
    // 親プロセスのexit
    exit(0);
}
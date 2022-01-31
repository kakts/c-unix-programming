/**
 * @file fork0.c
 * 
 * 5.4 forkの使用例
 * 
 * forkは下記の性質がある
    - 親プロセスには子プロセスのPIDを返す
    - 子プロセスには0を返す
    - エラー時は子プロセスが作られず、親プロセスに-1が返る。
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int i = 1234;
    pid_t pid; // process id
    pid_t fork_pid; // forkの戻り値のpid

    // fork前
    pid = getpid();
    printf("before: fork: pid\%d, i = %d\n", pid, i);
    fflush(stdout);

    // fork
    fork_pid = fork();

    // fork後
    pid = getpid();
    printf("after fork: pid=%d, i=%d, fork_pid=%d\n", pid, i, fork_pid);
    sleep(1); // このsleepは重要でない
    exit(0);
}
/**
 * @file mykill.c
 * 
 * 演習問題9.5
 * 引数にプロセス番号を受け取り、SIGTERMシグナルを送る
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "./a.out ${pid} \n");
        exit(1);
    }

    pid_t pid = strtol(argv[1], NULL, 10);
    if (errno == ERANGE) {
        perror("strtol");
        exit(1);
    }
    printf("killing process. id:%d", pid);
    kill(pid, SIGTERM);
    return 0;
}

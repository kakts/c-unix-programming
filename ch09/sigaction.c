/**
 * @file sigaction.c
 * 
 * コード例9.10 sigactionの利用例
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{
    fprintf(stderr, "@");
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0; // フラグは何も指定しない
    sigemptyset(&act.sa_mask); // ハンドラを起動したシグナル以外はブロックしない
    sigaction(SIGINT, &act, NULL);

    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
}
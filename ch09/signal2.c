/**
 * @file signal2.c
 * 
 * signal1.cを改良して、シグハルハンドラ関数内で、シグナルハンドラを再設定する
 * 
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{
    // シグナルハンドラを再設定する
    signal (SIGINT, handler);
    fprintf(stderr, "@");
}

int main(void)
{
    signal(SIGINT, handler);
    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
}
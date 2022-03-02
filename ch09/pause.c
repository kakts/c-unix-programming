/**
 * @file pause.c
 * 
 * pause(2)の実行例
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{
    fprintf(stderr, "handler\n");
}

int main(void)
{
    signal(SIGINT, handler);
    pause();
    fprintf(stderr, "hello, world\n");
}
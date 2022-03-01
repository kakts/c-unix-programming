/**
 * @file signal3.c
 * 
 * ^Cを押したらhelloを出力して実行を終了する
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig)
{
    fprintf(stderr, "hello\n");
    exit(0);
}

int main(void)
{
    signal(SIGINT, handler);
    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
}
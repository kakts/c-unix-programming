/**
 * @file kill.c
 * 
 * kill(2)、raise(2)のサンプル
 */

#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    fprintf(stderr, "handler\n");
}

int main(void)
{
    signal(SIGINT, handler);
    kill(getpid(), SIGINT);
    raise(SIGINT);
}

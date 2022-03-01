/**
 * @file signal4.c
 * 
 * 演習問題9.2
 * SIGINTを無視させる
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
    // SIG_IGNを指定すると、SIGINTを受け取った際に何もしなくなる
    signal(SIGINT, SIG_IGN);
    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
}
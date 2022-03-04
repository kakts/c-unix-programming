/**
 * @file bad-sleep.c
 * 
 * コード例9.11 競合状態のあるmy_sleep
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarm_handler(int sig) {
    // do nothing
}

void my_sleep(int seconds)
{
    signal(SIGALRM, alarm_handler);
    alarm(seconds);
    pause();
}

int main(void)
{
    printf("Hello(1)\n");
    my_sleep(3);
    printf("hello(2)\n");
}
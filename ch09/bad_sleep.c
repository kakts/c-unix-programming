/**
 * @file bad_sleep.c
 * 
 * 演習問題9.7
 * signal alarm pauseを使ってmy_sleepを定義する
 * void my_sleep(int seconds);
 * 
 * my_sleepはseconds秒後にSIGALRMが来るようにアラームクロックを仕掛ける
 * そしてpauseしてSIGALARMの到着を待つ。 SIGALRMが到着してもプロセスが終了しないように、シグナルハンドラを設定する必要がある
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigalrm_handler(int sig)
{
}

void my_sleep(int seconds)
{
    signal(SIGALRM, sigalrm_handler);
    alarm(seconds);
    pause();
}

int main(void)
{
   printf("start.\n");
   my_sleep(3); // 3秒待ってSIGALARMを発火して受け取るまで待つ
   printf("stop\n");
}
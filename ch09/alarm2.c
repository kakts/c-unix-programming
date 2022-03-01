/**
 * @file alarm2.c
 * 
 * 演習問題9.3 
 * alarm signalを使って3秒後にhelloを出力して終了する
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void loop (void) {
    int i;
    for (i = 0; i < 0xFFFFFF; i++) {
        // 時間稼ぎ用のループ
    }
}

/**
 * シグナルハンドラ関数
 * SIGALRMを受け取った時に実行数する
 */
void handler(int sig) {
    fprintf(stderr, "hello");
    exit(0);
}

int main(void)
{
    // alarm実行のシグナルハンドラを設定する
    signal(SIGALRM, handler);
    alarm(3);
    while (1) {
        loop(); // 時間稼ぎ
        printf(".");
        fflush(stdout);
    }
}
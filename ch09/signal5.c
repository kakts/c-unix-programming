/**
 * @file signal5.c
 * 
 * signalを使った場合、同じシグナルに対して1つまでしかブロックしないことを示すコード
 * 
 * signal5.cでは、SIGINTのハンドラ実行中に、SIGINTを4つ送っても、
 * その後のシグナルハンドラの起動は1回のみ。つまり3つのSIGINTは失われたことになる。
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{
    fprintf(stderr, "@");
    sleep(3); // 時間稼ぎ
}

int main(void)
{
    signal(SIGINT, handler);
    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
}

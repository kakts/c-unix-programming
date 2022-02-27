/**
 * @file signal1.c
 * 
 * signalを使ったシグナルハンドラの設定
 * 
 * 実行中に^Cを押すと、@を画面に表示する。
 * ^\をおしてSIGQUITを送信すると終了する
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * シグナルハンドラ用関数
 * 戻り値void
 * 引数 int
 */
void handler (int sig) 
{
    fprintf(stderr, "@");
}

int main(void)
{
    // SIGINTに対するハンドラを設定する
    signal(SIGINT, handler);

    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
}


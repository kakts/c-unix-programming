/**
 * @file 5.3.mypinfo.c
 * 
 * 自分自身のプロセスIDを表示し、さらに自分のプロセスの情報をpsコマンドで表示する
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = getpid();
    printf("pid = %d\n", getpid());

    // psコマンド用の文字列
    char command_str[100]  = "";

    // psコマンドの実行ようにコマンド生成

    // sprintfだとバッファオーバーフローを引き起こすので、snprintfを使う
    // sprintf(command_str, "ps -l -p %d", pid);
    if (snprintf(command_str, sizeof(command_str), "ps -l -p %d", pid) >= sizeof(command_str)) {
        fprintf(stderr, "too long command line (pid = %d)\n", pid);
        exit(1);
    }

    // コマンド実行
    system(command_str);

    exit(0);
}
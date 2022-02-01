/**
 * @file exec0.c
 * 
 * exec関数の実行例
 * 
 * execによって指定されたプログラムを実行する。
 * プロセスIDはそのまま
 */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Invoking ls.\n");
    fflush(stdout);
    execlp("ls", "ls", (char *) 0);

    // execlpに成功したらここは実行されない
    printf("Done.\n");
    return 0;
}
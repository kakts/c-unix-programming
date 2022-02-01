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
    /**
     * exec関数は、呼び出しプロセスのメモリ領域の内容を、新しいプログラムを実行するための内容で上書きしてしまう
     * exec呼び出し時点でstdioライブラリのバッファに残っているデータは、呼び出しが成功すると捨てられてしまう。
     */
    fflush(stdout);
    execlp("ls", "ls", (char *) 0);

    // execlpに成功したらここは実行されない
    printf("Done.\n");
    return 0;
}
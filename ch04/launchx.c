/**
 * @file launchx.c
 * 
 * 行バッファリングを試す
 * 
 * printfは標準出力に各関数
 * 5秒間の秒読みの後でgo!を表示したいが、標準出力が行バッファリングである環境で
 * このプログラムを実行すると、5から1までの数字は1秒ごとの表示されず、最後のgo!\nと同時に表示される
 * 
 * printfの直後にfflushするとそのたびにflushされるため、意図した表示になる
 */

#include <stdio.h>
#include <unistd.h>

int main(void) {
    int i;

    for (i = 5; i > 0; i--) {
        printf("%d", i);
        fflush(stdout);
        sleep(1);
    }

    printf(" go!\n");
    return 0;
}
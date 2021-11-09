// 1.2
#include <stdio.h>
#include <errno.h> // 変数errnoの宣言をしてくれる

int main (void) {
    errno = ENOENT;
    // errnoに基づいてエラーの原因を出力
    perror ("test");
}
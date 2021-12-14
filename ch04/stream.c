/**
 * @file stream.c
 * 
 * 標準入出力ライブラリを使う典型的な手順
 * 
 * exitは開いている全てのストリームを閉じる。
 * main からreturnした時にも全てのストリームが閉じられる(自動的にexitがよばれるため)
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 作ったストリームを受け取る変数
    FILE *fp;

    if ((fp = fopen("ch04/hello.txt", "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    /**
     * ストリームfpを使って読み書きをする
     */


    // ストリームを閉じる
    if (fclose(fp) == EOF) {
        perror("close");
        exit(1);
    }
    return 0;
}
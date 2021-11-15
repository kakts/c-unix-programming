/**
 * q1-9
 * argv[0]以外のコマンドライン引数は全部数字と仮定する
 * 
 * これらの数字全部を合計した数を表示するプログラムを作る
 * 文字列から整数の変換にはatoiかstrtolを使う
 * 
 * atoiは範囲外データを受け取ったときの扱いが不定のため、strtoiを使う
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h> // atoi

int main(int argc, char *argv[]) {
    if (argc < 1) {
        exit(1);
    }
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        int tmp_errno = errno;
        errno = 0;
        // 引数チェック用変数 整数に変換できない場合に、不正文字の先頭ポインタが返ってくる
        char *check;
        int data = strtol(argv[i], &check, 10);
        if (*check != '\0') {
            perror("strtoi: failed to convert");
            exit(EXIT_SUCCESS);
        }
        sum += data;

    }
    printf("result: sum is %d \n", sum);
}


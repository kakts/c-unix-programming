/**
 * @file 2-5.c
 * 
 * コマンドライン引数で与えた数字を配列dataに格納する
 * ただし配列の大きさは静的に10と決まっていて、11個以上の数字は格納できない
 * 
 * mallocを使って、この制限を取り払い、11個以上のデータでも扱えるようにする
 */

#include <stdio.h>
#include <stdlib.h> // atoi exit
#define N 10


/**
 * 動的にサイズを拡張できる版
 * 
 * 10個以上の引数でも、配列に格納できるようにする
 */
int main(int argc, char *argv [])
{
    int i;
    int data_size = argc - 1;

    // mallocで配列データサイズ確保
    // int✖︎要素数のサイズだけmallocで確保する
    int *a = (int *)malloc(data_size * sizeof(int));

    for (i = 1; i < argc; i++) {
        a[i - 1] = atoi(argv[i]);
    }

    for (i = 0; i < data_size; i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }
    return 0;
}

/**
 * 配列10個版
 * 引数から10個の数字を配列に詰める
 */
int orig_main(int argc, char *argv [])
{
    int i, data[N];
    // 指定した数以上の引数の場合は異常終了
    if (argc - 1 > N) {
        exit(1);
    }
    // i = 1からが数の引数
    for (i = 1; i < argc; i++) {
        data[i - 1] = atoi(argv[i]);
    }
    return 0;
}
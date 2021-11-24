/**
 * @file 2-3.c
 * 
 * 
 */

#include <stdio.h>

#include <stdlib.h> // free, malloc

/**
 * char buf  [1024]はローカル変数のポインタを返してしまっている
 * 配列bufはリターン時に消滅するのでポインタが指す値が宙ぶらりんになる
 * 
 * staticをつけることで解消できる
 * 
 * しかしこのコードには問題があり、itoaが再入可能でないことと、配列の大きさが1024バイトと固定されている
 */
char *itoa (int i)
{
    // ローカル変数のポインタを返してしまっている
    // char buf [1024];
    
    static char buf [1024];
    // 整数を文字列に変換
    snprintf(buf, sizeof(buf), "%d", i);
    return buf;
}

char *itoa2(int i)
{
    // 入力された引数の値によってサイズを変えれるようにしている
    // 第2引数が0の場合 snprintfは書き込みせず、書き込みに必要なバイト数を変えsう
    int n = snprintf(NULL, 0, "%d", i); // まず何バイト必要かを調べる
    char *buf = malloc(n+1); // メモリ領域を確保　NULL文字のために+1する
    snprintf(buf, n + 1, "%d", i);
    return buf;
}


int main(void)
{
    // char *p = itoa(1234);
    char *p = itoa2(1234);
    printf("p=%s\n", p);
    free(p); // pが指すメモ領域を解放
}
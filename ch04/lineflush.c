/**
 * @file lineflush.c
 * 
 * 行バッファリングのストリームでフラッシュが起きるのを確認する
 */
#include <stdio.h>

int main(void)
{
    int age;

    printf("How old are you? ");
    /**
     * 標準入力から読む
     * printfで標準出力に書いたHow old are you? が\nが入っていないのにscanfによって入力待ちになる時に
     * 出力される
     */
    scanf("%d", &age);
    printf("You are %d years old\n", age);
    return 0;
}
/**
 * @file 2-16.c
 * 
 * 変数xのnビット目の値(1or0)を返す関数check_bitを定義する
 */
#include <stdio.h>

/**
 * 変数xのnビット目の値を返す関数
 */
int check_bit(unsigned int x, int n) {

    // 1をnビット左シフトしたものとxを1ビットごとにANDする
    // 該当のビットが1の時だけ1を返す　それ以外は0を返す
    return (x & (1 << n)) != 0;
}

int main(void) {

    int i;
    for (i = 0; i < 31; i++) {
        printf("%d", check_bit(0x20, i));
    }
    printf("\n");
}
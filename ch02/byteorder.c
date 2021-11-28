/**
 * @file byteorder.c
 * 
 * intの大きさを4バイトと勝ち得して、バイトオーダを調べる
 */
#include <stdio.h>
int main (void)
{
    int i = 0x12345678;
    unsigned char *c = (unsigned char *) &i; // 1 byteごとに読むためにキャスト
    printf("%x:%x:%x:%x\n", c[0], c[1], c[2], c[3]);
}
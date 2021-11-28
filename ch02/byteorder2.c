/**
 * @file byteorder2.c
 * ファイルに書き込む
 */
#include <stdio.h>

int main(void)
{
    int i = 0x12345678;
    fwrite(&i, sizeof(i), 1, stdout);
}

/**
 * @file 2-1.c
 * 
 * ポインタ
 */
#include <stdio.h>
 
int main(void)
{
    char test, *p = &test;
    *p = 'A';
    printf("%c\n", *p);
}

// ポインタ変数pが初期化されていない
// int wrong_main(void)
// {
//     char *p;
//     *p = 'A';
//     printf("%c\n", *p);
// }
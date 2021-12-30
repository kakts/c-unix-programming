/**
 * @file q4-5.c
 * 
 *  
 */

#include <stdio.h>

int main(void)
{
    long long int x = 1234;
    char *s = "hello";
    // %dの指定だとwarningがでる
    printf("%d, %s\n", x, s);

    printf("%lld, %s\n", x, s);

    // xの値がintの範囲に収まることが分かっていれば
    printf("%d, %s\n", (int)x, s);
    return 0;
}
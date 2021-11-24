/**
 * @file func.c
 * 
 * 関数へのポインタ
 */
#include <stdio.h>

int add(int x, int y) {
    return x + y;
}

int mul (int x, int y) {
    return x * y;
}

int main(void)
{
    // 関数ポインタ
    int (*func) (int, int);
    func = add;

    printf("%d\n", func(10, 20));

    func = mul;
    printf("%d\n", func(10, 20));
}
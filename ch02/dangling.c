/**
 * @file dangling.c
 * 
 * dangling pointerの例
 */

#include <stdlib.h> // free, malloc

int main(void)
{
    int *p = malloc(sizeof(int));
    // 先に解放してしまう
    free(p);

    // 解放済みのメモリに対して書き込みしてしまう
    *p = 99;
}
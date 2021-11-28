/**
 * @file stdarg-add.c
 * 可変長引数のstdarg.hのマクロの使用例
 */

#include <stdio.h>
#include <stdarg.h>

// arg_numはここでは...の引数の個数
int add (int arg_num, ...)
{
    int i, sum = 0;
    // 可変長引数を表す変数pvarの定義
    va_list pvar;
    // 可変長引数pvarの使用開始 初期化
    va_start(pvar, arg_num);
    for (i = 0; i < arg_num; i++) {
        // 次の可変長を1つ、int型で取得
        sum += va_arg(pvar, int);
    }
    // 可変長引数pvarの使用終了
    va_end(pvar);
    return sum;
}

int main(void)
{
    printf("%d, %d, %d, %d\n", add(0), add(1, 10), add(2, 10, 20), add(3, 10, 20, 30));
}
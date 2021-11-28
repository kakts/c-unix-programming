/**
 * @file 2-18.c
 * 
 * stdarg.hを使って、printfを単純化したtiny_printfを定義する
 * - stdarg.hを使って可変長引数を扱えるようにする
 * - 書式に指定できる変換は%dのみ
 * - 第2引数移行には0-9だけを指定できる 文字コードはASCIIを仮定する
 * - 出力のためにはputcharだけを使う
 */
#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h>
#include <stdarg.h>

/**
 * format文の中から、intのプレースホルダ(%d)の数を集計する
 * 
 * "%d, %d, %d, %d" の場合 4
 */
int get_int_var_count(char format[]) 
{
    // formatから%dの個数のチェックをする
    int sum_of_arg = 0;
    int i = 0;
    
    while (i < strlen(format)) {
        char c = format[i];
        if (c == '%' && format[i + 1] == 'd') {
            sum_of_arg++;
            i+=2;
            continue;
        }
        i++;
    }
    return sum_of_arg;
}

int get_number_of_digits(int x) {
    int res = 1;
    // printf("x: %d\n", x);

    int target = x;
    while (1) {
        target = target / 10;
        // printf("a: %d\n", target);
        if (target == 0) {
            break;
        }
        res++;
    }
    return res;
}

/**
 * 自作 tiny_printf improve版
 * 桁数とか諸々自前で計算した
 * 
 * 問題文だと、数字は1桁前提になっているが、2桁以上の整数でも表示できるようになっている。
 */
void improve_tiny_printf(char format[], ...)
{
    // formatから%dの個数のチェックをする
    int sum_of_arg = get_int_var_count(format);

    int i = 0;
    int format_len = (int)strlen(format);
    
    
    va_list pvar;
    va_start(pvar, format);

    while (i <= format_len) {
        // printf("----\n");
        if (format[i] == '%' && format[i + 1] == 'd') {
            int tmp = va_arg(pvar, int);
            // printf("------tmp: %d", tmp);
            // 入力値の整数の桁数を入力
            int number_of_digits = get_number_of_digits(tmp);
            // printf("--number of digits:%d\n", number_of_digits);
            char converted[number_of_digits + 1];
            sprintf(converted, "%d", tmp);
            // 整数値の桁数分ループして文字出力
            for (int j = 0; j < number_of_digits; j++) {
                int res = putchar(converted[j]);
                if (res == EOF) {
                    exit(1);
                }
            }

            i+=2;
            continue;
        }
        putchar(format[i]);
        i++;
    }
    va_end(pvar);


}

int main(void)
{
    tiny_printf("test:%d, %d, %d aaa %d", 1100, 23001, 3, 4);
}
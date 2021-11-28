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

void tiny_printf(char format[], ...)
{
    // formatから%dの個数のチェックをする
    int sum_of_arg = get_int_var_count(format);

    int i = 0;
    int format_len = (int)strlen(format);
    
    
    va_list pvar;
    va_start(pvar, sum_of_arg);

    char res[strlen(format) - (2 * sum_of_arg)];
    int res_add_num = 0;
    while (i <= format_len) {
        if (format[i] == '%') {
            int tmp = va_arg(pvar, int);
            printf("tmp:%d", tmp);
            res[res_add_num] = tmp;
            i+=2;
            res_add_num++;
            continue;
        }
        res[res_add_num] = format[i];
        i++;
        res_add_num++;
    }
    va_end(pvar);

    
}

int main(void)
{
    tiny_printf("%d, %d, %d aaa %d", 1, 2, 3, 4);
}